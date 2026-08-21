# SDD In Action — 《规范驱动开发》配套代码

> 规范是第一手工件，代码是规范的衍生物。

本仓库是《规范驱动开发：AI 时代的软件工程新范式》的配套实战项目。

## 项目：智能日报生成器

一个用 SDD 方法论从零构建的完整项目，贯穿全书第 4-8 章。

## 目录结构

```
sdd-in-action/
├── specs/                    # 规范文档（第一手工件）
│   ├── proposal.md           # 需求规范（第 4 章）
│   ├── design.md             # 架构设计（第 5 章）
│   ├── tasks.md              # 任务分解（第 6 章）
│   ├── contracts/            # 接口契约
│   │   └── data-models.md    # 数据模型定义
│   └── adrs/                 # 架构决策记录
│       ├── 001-HTTP客户端选型.md   # ADR-001: httpx
│       ├── 002-数据存储方案.md     # ADR-002: SQLite
│       └── 003-采集层返回值封装.md  # ADR-003: CollectResult（第 7 章迭代产物）
├── src/                      # 生成的代码（衍生物，第 7 章开始）
├── tests/                    # 规范衍生的测试
├── templates/                # 可复用的 SDD 模板（附录）
└── examples/                 # 各章独立练习
    ├── ch01-vibe-coding-audit/       # 第 1 章：Vibe Coding 问题诊断
    ├── ch03-framework-comparison/    # 第 3 章：SDD 工具链对比实验
    └── (随章节逐步添加)
```

## 渐进式构建

本仓库随书的章节逐步成长：

| 章节 | 新增内容 | SDD 阶段 |
|------|---------|---------|
| 第 1 章 | `examples/ch01-vibe-coding-audit/` | 问题诊断 |
| 第 3 章 | `examples/ch03-framework-comparison/` | 工具对比 |
| 第 4 章 | `specs/proposal.md` | 需求分析 |
| 第 5 章 | `specs/design.md` + `specs/contracts/` + `specs/adrs/` | 架构设计 |
| 第 6 章 | `specs/tasks.md` | 任务拆解 |
| 第 7 章 | `src/` + `tests/` | 执行验证 |
| 第 8 章 | Agent 自动化流水线 | 模式应用 |

## 技术栈

- Python 3.11+
- Claude Code 作为 SDD 实践载体
- 具体技术选型在 `specs/design.md` 中定义（第 5 章）
