# 智能日报生成器 — 数据模型定义

## 1. 采集层输出模型

### CommitRecord（代码提交记录）

| 字段 | 类型 | 说明 |
|------|------|------|
| author | str | 提交者（GitHub 用户名） |
| message | str | commit message |
| timestamp | datetime | 提交时间 |
| repo | str | 仓库名称 |
| additions | int | 新增行数 |
| deletions | int | 删除行数 |
| files_changed | int | 变更文件数 |

### TaskRecord（任务变更记录）

| 字段 | 类型 | 说明 |
|------|------|------|
| assignee | str | 负责人（飞书用户名） |
| title | str | 任务标题 |
| status_from | str | 原状态 |
| status_to | str | 新状态 |
| updated_at | datetime | 变更时间 |

### MessageRecord（消息记录）

| 字段 | 类型 | 说明 |
|------|------|------|
| sender | str | 发送者（飞书用户名） |
| content | str | 消息内容（纯文本） |
| timestamp | datetime | 发送时间 |
| chat_name | str | 群名称 |

## 2. 生成层模型

### MemberReport（成员日报）

| 字段 | 类型 | 说明 |
|------|------|------|
| name | str | 成员姓名 |
| github_username | str | GitHub 用户名 |
| commits | list[CommitRecord] | 代码提交列表 |
| tasks | list[TaskRecord] | 任务变更列表 |
| messages | list[MessageRecord] | 相关消息列表 |

### DailyReport（日报）

| 字段 | 类型 | 说明 |
|------|------|------|
| date | date | 日报日期 |
| team_name | str | 团队名称 |
| members | list[MemberReport] | 各成员数据 |
| generated_at | datetime | 生成时间 |
| markdown | str | Markdown 格式日报 |
| html | str | HTML 格式日报 |

## 3. 身份映射

成员在不同系统中的账号通过 `config.yaml` 中的映射表关联：

```yaml
members:
  - name: "张三"
    github: "zhangsan"
    lark: "zhangsan@company.com"
  - name: "李四"
    github: "lisi-dev"
    lark: "lisi@company.com"
  - name: "王五"
    github: "wangwu"
    lark: "wangwu@company.com"
```

## 4. 模块接口契约

### 采集层

```python
# collector/github.py
def collect(repos: list[str], since: datetime, until: datetime) -> list[CommitRecord]

# collector/lark_task.py
def collect(project_id: str, since: datetime, until: datetime) -> list[TaskRecord]

# collector/lark_msg.py
def collect(chat_id: str, keywords: list[str], since: datetime, until: datetime) -> list[MessageRecord]
```

### 生成层

```python
# generator/formatter.py
def generate(members: list[MemberReport], date: date, team_name: str) -> DailyReport
```

### 推送层

```python
# notifier/email.py
def send(report: DailyReport, recipients: list[str]) -> bool

# notifier/lark_bot.py
def send(report: DailyReport, chat_id: str) -> bool
```

---

*规范版本：v1.0 | 对应《规范驱动开发》第 5 章*
