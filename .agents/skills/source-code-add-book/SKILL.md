---
name: source-code-add-book
description: Add or update a book/tutorial entry in `/Users/tomshine/Code/github-shine/source-code` by copying its cover and code into this repository and updating README.md under the chosen category. Supports two modes: (1) Douban mode — user pastes a Douban book link plus a local code directory; the skill fetches title/cover from Douban and fills README automatically; (2) manual mode — user provides title, cover file, and code dir. Use when working in the source-code repository and the user wants to 新增一本书, 豆瓣链接, 指定目录, add a book, add tutorial source, or update this repository's book index.
---

# Source Code Add Book

## Scope

Only for `/Users/tomshine/Code/github-shine/source-code`. Verify `pwd` first; if not this repo, stop.

## Inputs

Ask for missing items before editing:

- One of:
  - **Douban URL** (e.g. `https://book.douban.com/subject/26600689/`) — title, cover, and link are fetched automatically
  - **Book display title** (manual mode)
- **Code/source directory** to copy into `src/`
- **README category** heading (e.g. `编程语言 > Go`, `AI > 深度学习`); if the heading does not exist, ask whether to create it
- Manual mode only: cover file path
- Optional: official/GitHub URL, paired Chinese/English title notes

## Mode A — Douban link

1. Fetch the book page. Douban requires a browser User-Agent; plain requests get 403:

   ```bash
   curl -s -A "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0 Safari/537.36" "<douban-url>" -o /tmp/douban.html
   ```

2. Extract from `/tmp/douban.html`:
   - `<meta property="og:title" content="…" />` → display title
   - `<meta property="og:image" content="…" />` → cover URL
   - `<meta property="og:url" …/>` → Douban link for README

   Note: `<title>` tag carries a ` (豆瓣)` suffix; `og:title` does not — use `og:title`.

3. Download the cover **from the og:image URL to a temp file** (cover CDN needs UA plus a Douban Referer, else 418), then convert it with the utility script to the repo as `.webp`:

   ```bash
   curl -s -A "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0 Safari/537.36" -e "https://book.douban.com/" -o /tmp/book-cover "<og:image-url>"
   .agents/skills/source-code-add-book/scripts/convert-to-webp.sh /tmp/book-cover
   mv /tmp/book-cover.webp "images/<title>.webp"
   ```

   Replace `/\:*?"<>|` in the title with `-` for both cover filename and src dir name; keep Chinese characters as-is (matches existing entries like `30天自制操作系统`).

4. Copy the code directory — never move user originals:

   ```bash
   cp -R "<code-source-dir>" "src/<title-or-sanitized-name>/"
   ```

## Mode B — Manual inputs

```bash
cp "<cover-file>" "images/<title>.<ext>"
cp -R "<code-source-dir>" "src/<dest-dir>/"
```

Covers stay in their original format; run the file through `scripts/convert-to-webp.sh` if webp is wanted (same as Mode A).

## Utility script — convert-to-webp.sh

`scripts/convert-to-webp.sh` converts any non-webp image to `.webp` next to the original (originals kept). **Mode A uses it for every new Douban cover.**

```bash
.agents/skills/source-code-add-book/scripts/convert-to-webp.sh [-q 82] <file-or-dir>...
```

- `-q QUALITY` 0-100, default 82; directories scanned recursively; existing `.webp` skipped.
- Requires `cwebp` and `magick` in PATH (both at `/opt/homebrew/bin` on this machine).
- Use when the user asks to convert covers/a directory of images to webp, or supplies a non-webp cover from an external source.

## Update README (both modes)

Update only the requested category, matching existing local style:

```md
- [《标题》](./src/标题)

  > 豆瓣: [https://book.douban.com/subject/xxxx/](https://book.douban.com/subject/xxxx/)

  <img src="./images/标题.<ext>" width="300"/>
```

- Omit the `> 豆瓣:` block unless a Douban link was used; manual mode without any URL gets no URL block.
- Keep indentation/blank lines identical to nearby entries; do not bulk-format the file.
- If `src/<dest>` or `images/<cover>` already exists, stop and ask whether to replace, merge, or pick another name.

## Verify

```bash
test -d "src/<dest-dir>"
test -f "images/<cover-name>"
rg "src/<dest-dir>|images/<cover-name>" README.md
git status --short   # only this task's files
```

## Rules

- Do not modify other `src/*` books; do not bulk-format README.
- Do not invent metadata (author, publisher, URLs) the page/user did not provide.
- Do not add build tools, package files, or CI for this repository.
- Prefer `.jpg/.jpeg/.png/.webp/.gif` covers; unsupported extension → keep the file but mention it.
- Douban fetch/cover download fails after one retry with UA+Referer → fall back to Mode B; ask the user for the cover file.

## Report

After editing, report only: added code dir, cover file, README category, Douban link (if any), skipped optional metadata.
