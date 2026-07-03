# Agent 安装说明

你是正在帮助用户安装本地 Agent Skill 的 AI Agent。请按本文件操作，把当前目录安装为一个可被 Agent 调用的 skill。

## 目标

将当前 skill 目录安装为：

```text
happy-figure-skill-zh
```

安装完成后，目标目录下必须能直接看到：

```text
SKILL.md
README.md
references/
scripts/
```

不要只复制 `SKILL.md`。必须复制整个目录。

## 安装前检查

1. 确认当前目录包含 `SKILL.md`。
2. 确认当前目录包含 `references/` 和 `scripts/`。
3. 读取 `SKILL.md` frontmatter，确认 `name` 是 `happy-figure-skill-zh`。
4. 如果当前目录名是 `happy-figure-skill-zh-local`，安装到目标目录时改名为 `happy-figure-skill-zh`。

## 选择目标 Agent

如果用户明确指定了 Agent，只安装到对应位置。

| Agent | 安装目录 |
| --- | --- |
| Codex | `~/.agents/skills/happy-figure-skill-zh/` |
| Claude Code | `~/.claude/skills/happy-figure-skill-zh/` |
| Cursor | `~/.cursor/skills/happy-figure-skill-zh/` |
| Kiro 或其它 Agent | 先查该 Agent 的本地 skills / agents / extensions 目录；不确定时询问用户 |

如果用户没有指定 Agent，但当前运行环境能明确判断自己是哪一个 Agent，只安装到当前 Agent 的 skills 目录。不要默认同时安装到所有平台，除非用户明确要求。

## 安装步骤

把下面的 `<source-dir>` 替换为当前 skill 目录的绝对路径，把 `<target-dir>` 替换为上表中的目标目录。

```bash
mkdir -p "$(dirname "<target-dir>")"
cp -R "<source-dir>" "<target-dir>"
```

## 验证

安装后检查：

```bash
test -f "<target-dir>/SKILL.md"
test -d "<target-dir>/references"
test -d "<target-dir>/scripts"
```

再读取目标目录中的 `SKILL.md`，确认 frontmatter 仍然是：

```yaml
name: happy-figure-skill-zh
```

## 完成后告诉用户

安装完成后，告诉用户：

```text
已安装 Happy Figure Skill。可以在对话中这样使用：
使用 happy-figure-skill-zh，根据这篇论文生成图形摘要 prompt。
```

如果安装失败，说明失败原因、已完成的步骤、下一步需要用户提供什么信息。
