# Model Cards

Use model cards as light adaptation only. Do not replace the selected master prompt.

## Model choice

| Model | Best use | Adaptation |
| --- | --- | --- |
| Nano Banana Pro | Complex structure, stable redraws, final candidate diagrams | Use explicit zones, module positions, arrows, and forbidden content. Avoid conflicting style words. |
| Nano Banana 2 | Fast drafts, many labels, multi-version screening | Emphasize readable labels, exact text, and generate several drafts if the user later asks. |
| Qwen-image-2.0 | Chinese labels, Chinese research prompts, everyday academic schematics | Use concise Chinese labels and suppress poster/social-media style. |
| gpt-image-2 | High-aesthetic graphical abstracts, concept figures, overview figures, text-rich system diagrams | Constrain scientific structure clearly, allow richer controlled labels and short explanatory phrases when they improve workflow clarity, and let composition/whitespace remain moderately flexible. Do not force minimal-text mode solely because the figure has more than 10 labels. |
| Unknown | User has not chosen | Do not block generation to ask for a model. Default to a gpt-image-2 / strong text-rendering model friendly, model-neutral prompt with strong structure, controlled richer labels, and low-saturation academic style. Mention that a minimal-text or model-specific variant can be produced if needed. |

## Common constraints

Chinese:

```text
请严格遵守指定的科学结构，不要新增、删除、合并、重排或改写任何科学模块。不要编造数据、数值、曲线、图例、色标、公式、实验结果或测量标签。不要营销海报风，不要装饰图标，不要水印。
```

English:

```text
Strictly follow the specified scientific structure. Do not add, remove, merge, reorder, or reinterpret any scientific module. Do not invent quantitative data, values, curves, legends, color bars, equations, experimental results, or measurement labels. No marketing poster style, no decorative icons, no watermark.
```

## When to use a Visual Schema first

Use a two-stage Visual Schema when the figure has more than four regions, parallel flows, feedback loops, multi-level hierarchy, many labels, or strict layout requirements. Otherwise, a figure-type master can be used directly.
