# Language Strategy

Separate the user's explanation language, the copyable image-model prompt language, and the visible figure text language. The final prompt must state which text may appear inside the image.

## Three-language decision model

1. User-facing explanation language: follow the user's conversation language by default. For Chinese users, explain document understanding, basis, and caveats in Chinese.
2. Copyable image-model prompt language: choose the language that best controls the target image model and the target publication context.
   - For English papers, international venues, ACM/IEEE/NeurIPS/ICML/CVPR/ACL/KDD/WWW/SIGMOD/VLDB, and `gpt-image-2`, prefer an English final drawing prompt, even if the user speaks Chinese.
   - For Chinese theses, Chinese defense slides, Chinese reports, or Qwen-style Chinese-label diagrams, use a Chinese final drawing prompt.
   - For mixed cases, keep the user-facing explanation in Chinese but make the copyable final drawing prompt match the figure label language and venue language.
3. Visible figure text language: follow the target output artifact first, not the user's chat language.
   - English paper / international venue / SCI / ACM / IEEE / NeurIPS-style figure -> English labels.
   - Chinese thesis / proposal / defense / Chinese report -> Chinese labels.
   - If typography risk is high, use minimal-text mode with short labels.

## Modes

| Mode | Use when | Instruction to embed in the final prompt |
| --- | --- | --- |
| Chinese explanation + English final prompt + English labels | Chinese user, English paper, international venue, or `gpt-image-2` target | Use Chinese outside the copyable prompt; write the final drawing prompt in English; embed `All visible text in the figure must use only the following exact English labels...` |
| Chinese prompt + Chinese labels | Chinese thesis, Chinese defense, Chinese journal, Chinese report | `图中所有可见文字只能使用以下中文学术短语...` |
| English prompt + English labels | English user, English paper, international conference, English journal | `All visible text in the figure must use only the following exact English labels...` |
| Chinese prompt + English labels | Chinese user writing for an English paper, but target model follows Chinese instructions better | `请用中文理解绘图需求，但最终图中所有可见文字只能使用以下英文标签...` |
| Minimal text | User requests minimal text, typography must be exact, or known text-rendering risk | `尽量减少图中文字，只使用 A, B, C 等占位或极短模块标签...` |

## Required embedded label rule

For Chinese prompts, include this inside `最终绘图提示词`:

```text
图中所有可见文字只能使用以下内容：
1. "..."
2. "..."
3. "..."

不要生成列表之外的任何标题、图例、说明段、脚注、随机文字或结构字段。
```

For English prompts, use:

```text
All visible text in the figure must use only the following exact labels:
1. "..."
2. "..."
3. "..."

Do not render any title, legend, paragraph, footnote, random text, or structural field outside this list.
```

## Default label-density policy

Default to a clear, information-rich controlled-label version. Do not ask the user to choose between rich-label and minimal-label prompts before generating the first answer. After the main prompt, optionally mention that a minimal-text variant can be provided if the user needs cleaner typography, lower text-rendering risk, or a journal-style figure with fewer labels.

For system architecture diagrams, method pipelines, knowledge graph workflows, and graphical abstracts, include enough labels to make the process understandable. Prefer controlled rich labels over vague single-word labels. Minimal-text mode is an alternative variant, not the default.

## Model-aware label density

Label density is not fixed. Decide it from the drawing model, figure purpose, and text-rendering risk.

- For `gpt-image-2` or other strong text-rendering image models, allow richer labels and short explanatory phrases when they clarify the scientific workflow. Do not switch to minimal-text mode only because the label list exceeds 10 items. A complex system figure may reasonably use 12-25 concise controlled labels.
- For `Nano Banana Pro`, use moderate-to-rich labels when the workflow needs clarity, but keep labels concise and place them inside explicit zones.
- For `Nano Banana 2` and `Qwen-image-2.0`, prefer shorter labels; use minimal-text mode when many labels are long, dense, or likely to be misrendered.
- Use minimal-text mode when the user explicitly asks for it, when typography must be publication-perfect, or when the figure is too dense for readable text.

## Label guidance

- Prefer concise labels over full sentences, but do not remove necessary process labels when the model can handle them.
- Preserve technical terms exactly.
- Long labels should be shortened into clear academic phrases instead of replaced by vague words.
- Do not ask the user to handle labels separately. The label restriction belongs inside the final drawing prompt.
