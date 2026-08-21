#!/usr/bin/env bash
# Convert image files to .webp next to the originals (originals are kept).
# Usage: convert-to-webp.sh [-q QUALITY] <file-or-dir>...
#   -q QUALITY  webp quality 0-100, default 82
#   jpg/jpeg/png -> cwebp ; gif/tif/tiff/bmp -> magick (first frame)
#   directories are scanned recursively; existing .webp files are skipped.
set -euo pipefail

q=82
args=()
while [ $# -gt 0 ]; do
  case "$1" in
    -q) q="$2"; shift 2 ;;
    -*) echo "unknown option: $1" >&2; exit 2 ;;
    *) args+=("$1"); shift ;;
  esac
done
[ "${#args[@]}" -gt 0 ] || { echo "usage: $0 [-q QUALITY] <file-or-dir>..." >&2; exit 2; }

convert() {
  local f="$1"
  case "${f##*.}" in
    webp) return ;;
    gif|tif|tiff|bmp) magick "$f" -quality "$q" "${f%.*}.webp" ;;
    *) cwebp -quiet -q "$q" "$f" -o "${f%.*}.webp" ;;
  esac
}

for a in "${args[@]}"; do
  if [ -d "$a" ]; then
    while IFS= read -r -d '' f; do convert "$f"; done < <(find "$a" -type f \( -iname '*.jpg' -o -iname '*.jpeg' -o -iname '*.png' -o -iname '*.gif' -o -iname '*.tif' -o -iname '*.tiff' -o -iname '*.bmp' \) -print0)
  else
    convert "$a"
  fi
done