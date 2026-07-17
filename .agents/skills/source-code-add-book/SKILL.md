---
name: source-code-add-book
description: Add a new book/tutorial entry only in `/Users/tomshine/Code/github-shine/source-code` by copying its cover and code into this repository and updating README.md under the chosen category. Use when working in the source-code repository and the user wants to 新增一本书, add a book, add tutorial source, 指定封面位置, 指定代码位置, or update this repository's book index.
---

# Source Code Add Book

## Scope

This skill is only for `/Users/tomshine/Code/github-shine/source-code`.

Before doing anything, verify:

```bash
pwd
```

If the current directory is not `/Users/tomshine/Code/github-shine/source-code`, stop and say this skill is scoped to that repository.

## Inputs to collect

Ask for any missing item before editing:

- Book display title for `README.md`
- Category path in `README.md` headings, e.g. `编程语言 > Go`, `AI > 深度学习`
- Cover file path
- Code/source directory path
- Optional official URL / GitHub URL / download URL
- Optional Chinese/English paired titles or notes

## Workflow

1. Inspect the current repo shape:

   ```bash
   pwd
   rg '^#{2,4} ' README.md
   find images src -maxdepth 1 -type d -o -type f
   ```

2. Pick destination names:

   - Code goes to `src/<book-or-repo-name>/`.
   - Cover goes to `images/<book-title-or-existing-style>.<ext>`.
   - Preserve existing naming style; do not rename unrelated files.
   - If destination exists, stop and ask whether to replace, merge, or choose another name.

3. Copy files, do not move user originals:

   ```bash
   cp -R "<code-source-dir>" "src/<dest-dir>"
   cp "<cover-file>" "images/<cover-name>"
   ```

4. Update `README.md` in the requested category only.

   Use the existing local pattern:

   ```md
   - [《Book Title》](./src/dest-dir)

     > Github: [https://example.com](https://example.com)

     <img src="./images/cover-name.jpg" width="300"/>
   ```

   Omit URL block if no URL was provided. Keep indentation and blank lines consistent with nearby entries.

5. Verify paths:

   ```bash
   test -d "src/<dest-dir>"
   test -f "images/<cover-name>"
   rg "src/<dest-dir>|images/<cover-name>" README.md
   git status --short
   ```

## Rules

- Do not bulk-format `README.md`.
- Do not modify other `src/*` book directories.
- Do not invent metadata the user did not provide.
- Do not add build tools, package files, or CI for this repository.
- Do not run outside `/Users/tomshine/Code/github-shine/source-code`.
- If the requested category heading does not exist, ask whether to create it and where.
- If cover extension is unsupported by Markdown preview, keep the file but mention it; prefer `.jpg`, `.jpeg`, `.png`, `.webp`, `.gif`.

## Response format

After editing, report only:

- Added code directory
- Added cover file
- Updated README category
- Any skipped optional metadata
