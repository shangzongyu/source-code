#!/usr/bin/env python3
from pathlib import Path
import shutil
import subprocess
from typing import Iterable, NamedTuple

import typer
from rich.console import Console
from rich.progress import BarColumn, Progress, TextColumn, TimeElapsedColumn
from rich.table import Table

IMAGE_EXTS = {".jpg", ".jpeg", ".tif", ".tiff", ".bmp", ".webp", ".png"}
VIDEO_EXTS = {".mp4", ".mov", ".mkv", ".avi", ".webm"}

app = typer.Typer(add_completion=False)
console = Console()


class Item(NamedTuple):
    src: Path
    rel: Path


def size_text(size: int) -> str:
    units = ["B", "KB", "MB", "GB"]
    value = float(size)
    for unit in units:
        if value < 1024 or unit == units[-1]:
            return f"{value:.1f}{unit}" if unit != "B" else f"{size}B"
        value /= 1024
    return f"{size}B"


def is_under(path: Path, parent: Path) -> bool:
    try:
        path.resolve().relative_to(parent.resolve())
        return True
    except ValueError:
        return False


def collect(inputs: Iterable[Path], out_dir: Path) -> list[Item]:
    files: list[Item] = []
    exts = IMAGE_EXTS | VIDEO_EXTS
    for item in inputs:
        path = item.expanduser()
        if path.is_dir():
            files.extend(
                Item(child, child.relative_to(path))
                for child in path.rglob("*")
                if child.is_file()
                and child.suffix.lower() in exts
                and not is_under(child, out_dir)
            )
        elif path.is_file() and path.suffix.lower() in exts and not is_under(path, out_dir):
            files.append(Item(path, Path(path.name)))
        elif not path.exists():
            raise typer.BadParameter(f"not found: {path}")
    return files


def png_cmd(src: Path, dst: Path, palette: bool) -> list[str]:
    cmd = ["ffmpeg", "-nostdin", "-hide_banner", "-loglevel", "error", "-y", "-i", str(src)]
    if palette:
        cmd += ["-vf", "palettegen=stats_mode=full[p];[0:v][p]paletteuse=dither=sierra2_4a"]
    return cmd + ["-compression_level", "9", "-pred", "mixed", str(dst)]


def mp4_cmd(src: Path, dst: Path, codec: str, crf: int, preset: str, audio_bitrate: str) -> list[str]:
    video = ["-c:v", "libx264", "-preset", preset, "-crf", str(crf)]
    if codec == "h265":
        video = ["-c:v", "libx265", "-preset", preset, "-crf", str(crf)]
    return [
        "ffmpeg", "-nostdin", "-hide_banner", "-loglevel", "error", "-y",
        "-i", str(src),
        "-map", "0:v:0", "-map", "0:a?",
        *video,
        "-c:a", "aac", "-b:a", audio_bitrate,
        "-movflags", "+faststart",
        str(dst),
    ]


def output_for(src: Path, rel: Path, out_dir: Path) -> Path:
    parent = rel.parent
    if src.suffix.lower() in IMAGE_EXTS:
        return out_dir / parent / f"{src.stem}.png"
    return out_dir / parent / f"{src.stem}.mp4"


def temp_for(dst: Path) -> Path:
    return dst.with_name(f".{dst.name}.tmp{dst.suffix}")


@app.command()
def main(
    inputs: list[Path] = typer.Argument(..., help="Files or directories."),
    output: Path = typer.Option(Path("compressed_media"), "-o", "--output", help="Output directory."),
    palette: bool = typer.Option(False, "--palette", help="Smaller PNG, may reduce color quality."),
    crf: int = typer.Option(23, "--crf", min=0, max=51, help="MP4 quality: lower is clearer/larger."),
    preset: str = typer.Option("medium", "--preset", help="x264 preset."),
    audio_bitrate: str = typer.Option("128k", "--audio-bitrate", help="MP4 audio bitrate."),
    codec: str = typer.Option("h264", "--codec", help="Video codec: h264 or h265."),
    overwrite: bool = typer.Option(False, "--overwrite/--no-overwrite", help="Replace existing outputs."),
):
    if not shutil.which("ffmpeg"):
        console.print("[red]ffmpeg not found[/red]")
        raise typer.Exit(1)

    out_dir = output.expanduser()
    out_dir.mkdir(parents=True, exist_ok=True)
    files = collect(inputs, out_dir)
    if codec not in {"h264", "h265"}:
        raise typer.BadParameter("--codec must be h264 or h265")
    if not files:
        console.print("[yellow]nothing to do[/yellow]")
        raise typer.Exit()

    table = Table(title=f"Compressed {len(files)} file(s)")
    table.add_column("File")
    table.add_column("Output")
    table.add_column("Original", justify="right")
    table.add_column("Compressed", justify="right")
    table.add_column("After/Original", justify="right")
    table.add_column("Saved", justify="right")
    table.add_column("Status")

    progress = Progress(
        TextColumn("[bold blue]{task.description}"),
        BarColumn(),
        TextColumn("{task.completed}/{task.total}"),
        TimeElapsedColumn(),
        console=console,
    )

    with progress:
        task = progress.add_task("compressing", total=len(files))
        total_before = 0
        total_after = 0
        kept = 0
        skipped = 0
        for item in files:
            src = item.src
            dst = output_for(src, item.rel, out_dir)
            before = src.stat().st_size
            total_before += before
            if src.resolve() == dst.resolve():
                total_after += before
                skipped += 1
                progress.advance(task)
                continue
            if dst.exists() and not overwrite:
                total_after += before
                skipped += 1
                table.add_row(src.name, str(dst), size_text(before), "-", "-", "-", "exists")
                progress.advance(task)
                continue

            dst.parent.mkdir(parents=True, exist_ok=True)
            tmp = temp_for(dst)
            cmd = (
                png_cmd(src, tmp, palette)
                if src.suffix.lower() in IMAGE_EXTS
                else mp4_cmd(src, tmp, codec, crf, preset, audio_bitrate)
            )
            subprocess.run(cmd, check=True)
            after = tmp.stat().st_size
            ratio = after / before * 100 if before else 0
            saved = 100 - ratio
            status = "kept"
            if after >= before:
                tmp.unlink()
                after = before
                total_after += after
                ratio = 100
                saved = 0
                status = "skipped larger"
                skipped += 1
            else:
                tmp.replace(dst)
                total_after += after
                kept += 1
            table.add_row(
                src.name,
                str(dst),
                size_text(before),
                size_text(after),
                f"{ratio:.1f}%",
                f"{saved:.1f}%",
                status,
            )
            progress.advance(task)

    total_ratio = total_after / total_before * 100 if total_before else 0
    total_saved = 100 - total_ratio
    table.add_section()
    table.add_row(
        "total",
        f"{kept} kept, {skipped} skipped",
        size_text(total_before),
        size_text(total_after),
        f"{total_ratio:.1f}%",
        f"{total_saved:.1f}%",
        "",
    )
    console.print(table)


if __name__ == "__main__":
    app()
