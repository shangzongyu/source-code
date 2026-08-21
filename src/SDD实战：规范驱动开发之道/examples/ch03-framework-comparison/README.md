# 练习：SDD 工具链对比实验

> 对应《规范驱动开发》第 3 章

## 目标

用同一个小需求，分别用三种方式创建规范，体验不同工具链的差异。

## 实验需求

> 做一个 CLI 工具，输入一个 GitHub 仓库 URL，输出该仓库的基本统计信息（星标数、Fork 数、最近更新时间、主要语言）。

## 实验一：纯手工 Markdown（最小方案）

在项目根目录创建 `specs/` 文件夹，手动编写：

```bash
mkdir -p specs
```

然后用你最熟悉的编辑器创建以下文件：

- `specs/proposal.md` — 需求规范（5-10 行即可）
- `specs/tasks.md` — 任务分解（3-5 个任务）

完成后，把 `specs/proposal.md` 的内容粘贴给你的 AI 编程工具，让它按规范生成代码。

**体验重点**：感受"先写规范再写代码"和"直接告诉 AI 要做什么"的区别。

## 实验二：用 OpenSpec 的斜杠命令

如果你使用的 AI 工具支持 OpenSpec：

```bash
npm install -g @fission-ai/openspec@latest
openspec init
```

然后在 AI 工具中使用：
- `/opsx:propose` — 创建提案
- `/opsx:apply` — 执行实现
- `/opsx:verify` — 验证实现

**体验重点**：对比有框架和无框架时，规范的结构化程度有何不同。

## 实验三：用 spec-kit 的正式流程

如果你安装了 spec-kit：

```bash
uv tool install specify-cli --from git+https://github.com/github/spec-kit.git
specify init gh-stats-cli --ai claude
```

然后在 AI 工具中使用：
- `/speckit.specify` — 定义需求
- `/speckit.plan` — 创建技术方案
- `/speckit.tasks` — 生成任务清单
- `/speckit.implement` — 执行实现

**体验重点**：感受 spec-kit 的正式性——Constitution、跨文档一致性检查。

## 对比记录表

完成实验后，填写以下对比表：

| 维度 | 纯手工 Markdown | OpenSpec | spec-kit |
|------|---------------|----------|----------|
| 写规范花了多久 | | | |
| 规范的结构化程度（1-5） | | | |
| AI 生成代码的准确度（1-5） | | | |
| 整体体验 | | | |

## 下一步

带着你的对比记录继续阅读第 4 章。第 4 章将用贯穿全书的项目演示完整的需求分析流程——无论你选择了哪种工具链，方法论是通用的。
