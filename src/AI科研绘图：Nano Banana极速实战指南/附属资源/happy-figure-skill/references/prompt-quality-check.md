# Prompt Quality Check

Use this as a final pass before returning the prompt.

## Check the prompt

- The selected master structure is preserved.
- The field style matches the detected discipline. For CS/ML prompts, check both Content Community and Visual Treatment: the content community should match the paper topic, and any Premium Academic Graphical Abstract treatment should still preserve CS system-diagram logic rather than drifting into biomedical, materials-science, or generic journal visual language.
- The target figure type is explicit.
- The research object and content focus come from the provided document.
- The layout, modules, arrows, and relationships are concrete.
- The prompt does not ask the drawing model to invent data, curves, measurements, experimental results, microscopy content, or photo evidence.
- The phrase `图中所有可见文字只能使用以下内容` or the English equivalent appears inside the final prompt.
- The final prompt does not contain unresolved scaffolding or placeholders such as `{VISIBLE_TEXT_RULE}`, `[Paste the full Visual Schema here]`, `[Insert extracted research context]`, `[Label ...]`, `---BEGIN PROMPT---`, or `---END PROMPT---`.
- The visible text list contains only concise labels.
- The prompt includes forbidden-content constraints and does not request forbidden content.
- Model adaptation is short and does not override the master prompt.
- No unrelated toolchain suggestions appear.

## Short review reminder

Use one concise sentence outside the final prompt:

```text
生成后请重点审查科学结构、箭头关系、图中文字、数据边界和目标期刊要求。
```

For real data charts, microscopy images, experimental photos, or factual image repair requests, use:

```text
涉及真实数据或实证图像时，请不要让绘图模型编造、修补或改写事实证据；生成结果只能作为示意构图参考，并需作者审查。
```
