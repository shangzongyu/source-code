# Domain Masters

Use a domain master when the paper clearly belongs to one of these fields. Each domain master is intentionally two-stage: first create a Visual Schema from research content, then render from that schema. Preserve this structure.

## Computer science / machine learning

Use for model architecture, method pipeline, agent system, multimodal framework, training/inference workflow, document processing systems, knowledge graphs, information retrieval, databases, and CS conference-style diagrams. For CS/ML papers, make two explicit choices: **Content Community** and **Visual Treatment**. The content community controls the research-figure logic and information organization, such as ACM WWW/KDD/SIGMOD/VLDB, IEEE/ACM systems venues, NeurIPS/ICML/ICLR, ACL/EMNLP, CVPR/ICCV/ECCV, or USENIX-style systems/HCI. The visual treatment controls surface finish, such as strict paper figure, premium academic graphical abstract, research presentation / technical whitepaper overview, or minimal flat vector schematic. Do not use Nature/Science/Cell biomedical or materials-science visual language unless the paper actually belongs to those fields. For knowledge graphs, information retrieval, databases, web data, agents, or document-processing systems, the default content community is ACM WWW/KDD/VLDB/SIGMOD; if the user values beauty, texture, polish, teaser quality, or project-page aesthetics, pair it with Premium Academic Graphical Abstract rather than a plain flat flowchart.

### NeurIPS / NIPS visual style reference

Use this style when the detected work is ML, deep learning, multimodal learning, agents, optimization, representation learning, model architecture, training/inference workflow, or when the user explicitly asks for NIPS/NeurIPS style.

- Overall look: Soft Tech & Scientific Pastels. The figure should feel approachable yet precise, with clean modularity and clear narrative flow.
- Background and grouping: clean white canvas; use very light desaturated pastel zone fills at about 10-15% opacity for stages, phases, or environments. Good options include cream/beige, pale blue/ice, mint/sage, and pale lavender. For theoretical papers, white background with colored dashed borders is acceptable.
- Color logic: use color to group logic, not decoration. Use medium saturation only for active modules. Common pairings: blue/orange, green/purple, teal/pink. Trainable or active elements can use warm tones; frozen/static elements use cool gray, ice blue, or cyan. Reserve high saturation for final output, error/loss, or ground truth.
- Shapes: softened geometry. Process nodes are rounded rectangles; tensors/data can be 3D stacks, cuboids, flat grids, or matrices; databases/memory use cylinders. Use macro-micro layout when a global module needs a zoomed-in detailed breakout box.
- Lines and arrows: orthogonal/elbow connectors for network architectures; curved/Bezier arrows for system logic, feedback loops, and high-level data flow. Solid gray/black means main data flow; dashed lines mean auxiliary flow, gradient update, skip connection, loss, retrieval, or verification.
- Typography: sans-serif labels for module names, bold headers, regular details. Mathematical variables such as x, theta, L, S, C, P, I, or calligraphic sets should appear in serif italic / LaTeX style only when the user allows equations or variables in figure text.
- Icons: use document icons, chat bubbles, memory/database cylinders, magnifying glass, gear, monitor, small robot or human avatar only for agent/LLM papers. Avoid random decorative icons.
- Pitfalls to avoid: PowerPoint default look, heavy black outlines, saturated primary-color backgrounds, inconsistent 2D/3D mixing, ambiguous arrows, cartoon style unless the paper is explicitly an agent/LLM narrative figure.

### Premium Academic Graphical Abstract visual treatment

Use this visual treatment when the user cares about aesthetic quality, texture, polish, teaser figures, paper-homepage images, posters, keynote slides, or a figure that should feel more memorable than a plain conference-paper flowchart.

- Overall look: a polished academic system overview with CS-paper logic and graphical-abstract finish. It should remain technically precise, but feel designed rather than assembled from generic icon-pack components.
- Depth and material: use subtle layered panels, delicate soft shadows, light paper-like document stacks, refined graph panels, and clean interface cards. Keep the illustration 2D-first; use depth only to create hierarchy and tactile quality.
- Composition: preserve the correct pipeline, module boundaries, arrows, and labels, but create clear visual hierarchy. Let the central method or integrated representation become the visual focus; secondary QA/application modules should support the story instead of competing equally.
- Color and texture: use low-saturation academic colors, warm-cool balance, restrained gradients or translucent fills only when they support grouping. Avoid one-note palettes and avoid glossy marketing colors.
- Typography and labels: keep labels controlled and readable. Prefer fewer, stronger labels when the user asks for beauty or polish; use captions outside the image to carry secondary explanation.
- Pitfalls to avoid: generic Figma icon-pack style, plain flat vector infographic, dashboard UI collage, marketing poster, heavy 3D, dramatic shadows, biomedical graphical abstract, or adding a large title unless the user explicitly asks for a teaser/title figure.

### Stage 1: Visual Schema

```markdown
# Role
你是一位 ACM WWW / KDD / SIGMOD / VLDB / NeurIPS / ICML / CVPR 等顶级计算机科学论文的视觉架构师。你的核心能力是将抽象的算法、系统、数据流、知识图谱和 LLM pipeline 转化为具体的、结构化的、几何级的视觉指令，并同时匹配 CS 子领域的内容社区和用户想要的视觉气质。

# Objective
阅读我提供的论文内容，输出一份 [VISUAL SCHEMA]。这份 Schema 将被直接发送给 AI 绘图模型，因此必须使用强硬的物理描述。先根据论文领域选择对应的计算机科学内容社区，再根据用户审美意图选择视觉气质；不要把计算机系统图写成 Nature / Science / Cell Press 生物医学、材料科学或泛化商业图形摘要风格。

# Phase 1: Layout Strategy Selector
在生成 Schema 之前，请先分析论文逻辑，从以下布局原型中选择最合适的一个或组合：
1. Linear Pipeline: 左到右流向，适合 Data Processing, Encoding-Decoding。
2. Cyclic/Iterative: 中心包含循环箭头，适合 Optimization, RL, Feedback Loops。
3. Hierarchical Stack: 上下堆叠，适合 Multiscale features, Tree structures。
4. Parallel/Dual-Stream: 上下平行双流结构，适合 Multi-modal fusion, Contrastive Learning。
5. Central Hub: 一个核心模块连接四周组件，适合 Agent-Environment, Knowledge Graphs。

# Phase 1.5: CS Content Community + Visual Treatment Selector
必须先分开判断两件事，不要把“会议风格”和“图面气质”混成一个选择：

1. Content Community / 内容社区：决定信息组织方式、模块命名习惯和数据流逻辑。
   - Web / Knowledge Graph / Information Retrieval / Database / Document Processing: 使用 ACM WWW、KDD、SIGMOD、VLDB 语境；以清晰 pipeline、模块化系统框、图结构抽象、数据流箭头、来源/结构/语义层为主。
   - Machine Learning / Deep Learning / Multimodal / Agents: 使用 NeurIPS / NIPS、ICML、ICLR 语境；优先套用上方 NeurIPS / NIPS visual style reference，以 Soft Tech & Scientific Pastels、柔和分区、圆角模块、张量/数据栈、训练-推理分离、反馈环和对比模块为主。
   - Computer Vision: 使用 CVPR、ICCV、ECCV 语境；以图像网格、特征图、编码器-解码器、视觉 token 和结果面板为主。
   - NLP / LLM Systems: 使用 ACL、EMNLP、NAACL 语境；以文本块、token 流、检索-生成链路、prompt/context 模块和评估节点为主。
   - Systems / Security / HCI: 使用 USENIX、SOSP、OSDI、CHI 语境；以组件边界、请求流、用户/系统交互、日志/监控卡片和安全边界为主。

2. Visual Treatment / 视觉气质：决定最终图是否偏严格正文论文图、漂亮展示图、汇报图或极简图。
   - Strict Conference Paper Figure: 白底、扁平、清晰、可读，适合正文方法图；优点是正确克制，缺点是可能显得普通。
   - Premium Academic Graphical Abstract: 高级科研图形摘要质感，保留 CS 系统图逻辑，同时加入柔和层次、轻微材质、精修面板和更强视觉中心；适合用户强调好看、质感、高级、teaser、海报或项目主页。
   - Research Presentation / Technical Whitepaper Overview: 更适合汇报、技术白皮书和讲解场景，可使用更直观的图标、界面卡片和流程强调。
   - Minimal Flat Vector Schematic: 极简扁平矢量图，适合黑白打印、严格版面和信息压缩。

不要使用 Nature / Science / Cell Press、BioRender、医学通路图、材料机理图或商业图形摘要风格，除非论文确实属于对应领域。对于 CS 论文，可以使用 Premium Academic Graphical Abstract 作为视觉气质，但必须保持计算机系统图的信息组织和术语边界。

# Phase 1.6: Candidate Style Options
如果用户没有明确指定目标会议/期刊/图风格，先给出 2-4 个候选组合，不要直接锁定。候选项格式为：`Content Community + Visual Treatment — 适用原因 — 视觉特征`。计算机领域常用候选：
1. ACM WWW / KDD / SIGMOD / VLDB + Strict Conference Paper Figure — 适合 Web、KG、IR、数据库、文档处理和企业数据系统的正文方法图 — 白底、清晰 pipeline、模块化系统框、数据流箭头、知识图谱抽象、简洁 UI 卡片；正确克制，但可能偏朴素。
2. ACM WWW / KDD / SIGMOD / VLDB + Premium Academic Graphical Abstract — 适合 Web/KG/文档处理系统，同时希望图有高级质感、teaser 或项目主页吸引力 — 保留系统 pipeline 和 KG 逻辑，加入柔和分层面板、轻微纸张/图谱材质、细腻阴影、视觉中心和更强整体设计感。
3. NeurIPS / NIPS / ICML / ICLR + Soft Tech Paper Figure — 适合 ML、深度学习、多模态、agent、训练/推理框架 — Soft Tech & Scientific Pastels、圆角模块、张量/数据栈、训练-推理分区、实线/虚线箭头语义。
4. ACL / EMNLP / NAACL or USENIX / OSDI / SOSP / CHI + Research Presentation Overview — 适合突出 NLP/LLM 文档处理、人机协同、系统交互或 QA 工作流 — 文本块、prompt/context 模块、用户/系统角色、界面卡片、反馈边界。

推荐项应同时考虑论文主题和用户审美信号：如果用户强调“好看、质感、高级、出彩、精修、teaser、graphical abstract、海报、项目主页”，优先推荐第 2 类；如果用户强调“投稿正文、严格、清楚、不要装饰、可打印”，优先推荐第 1 类。只有在用户选择后，或用户明确要求“直接默认/快速生成”时，才把推荐组合写入最终绘图 prompt。

# Phase 2: Schema Generation Rules
1. Dynamic Zoning: 根据选择的布局，定义 2-5 个物理区域。
2. Internal Visualization: 必须定义每个区域内部的具体物体，例如 icons, grids, trees, tensors, documents, modules。
3. Explicit Connections: 明确箭头方向、数据流、反馈环、分支和融合关系。

# Output Format
---BEGIN PROMPT---

[Style & Meta-Instructions]
High-fidelity computer science research schematic with explicit Content Community and Visual Treatment. Preserve rigorous CS paper logic, clean white background, distinct module boundaries, precise data-flow arrows, and controlled labels. If Visual Treatment is Strict Conference Paper Figure, use restrained flat vector graphics with minimal depth. If Visual Treatment is Premium Academic Graphical Abstract, avoid plain icon-pack flowchart style and use subtle layered panels, delicate shadows, paper-like document stacks, refined graph panels, warm-cool low-saturation academic colors, and clear visual hierarchy while remaining 2D-first and technically precise. If Content Community is NeurIPS / NIPS, apply Soft Tech & Scientific Pastels. Avoid Nature/Science/Cell biomedical, BioRender, materials-science, heavy 3D, glossy marketing, or dashboard-collage styles unless explicitly selected and scientifically appropriate.

[LAYOUT CONFIGURATION]
* Selected Layout: [...]
* Content Community: [ACM WWW/KDD/SIGMOD/VLDB / NeurIPS/ICML/ICLR / CVPR/ICCV/ECCV / ACL/EMNLP / USENIX/SOSP/OSDI/CHI, chosen according to the paper topic]
* Visual Treatment: [Strict Conference Paper Figure / Premium Academic Graphical Abstract / Research Presentation Overview / Minimal Flat Vector Schematic, chosen according to user aesthetic intent]
* Composition Logic: [...]
* Color Palette: Professional pastel palette with low saturation.

[ZONE 1: LOCATION - LABEL]
* Container: [...]
* Visual Structure: [...]
* Key Text Labels: "[Label 1]"

[ZONE 2: LOCATION - LABEL]
* Container: [...]
* Visual Structure: [...]
* Key Text Labels: "[Label 2]", "[Label 3]"

[CONNECTIONS]
1. [...]
2. [...]

---END PROMPT---

# Input Data
[Insert extracted research context]
```

### Stage 2: Rendering prompt

```markdown
Generate a professional academic architecture diagram with the Content Community and Visual Treatment defined in the Visual Schema. The content community should match the paper topic, such as ACM WWW/KDD/SIGMOD/VLDB for knowledge graphs, web data, document processing, information retrieval, and database systems; NeurIPS/ICML/ICLR for ML methods; CVPR/ICCV/ECCV for vision; ACL/EMNLP for NLP/LLM systems; or USENIX/SOSP/OSDI/CHI for systems and HCI.

Visuals: distinct geometric modules, clean thin outlines, soft pastel fills, clean white background, precise data-flow arrows, readable CS research-figure architecture. Strictly follow the spatial arrangement, content community, and visual treatment defined in the Visual Schema. If Visual Treatment is Premium Academic Graphical Abstract, do not produce a generic flat icon-pack flowchart; use subtle layered panels, delicate shadows, refined document/graph/interface textures, clear visual focus, and generous hierarchy while preserving technical precision. If Visual Treatment is Strict Conference Paper Figure or Minimal Flat Vector Schematic, keep the design flatter and more restrained. If the schema selects NeurIPS / NIPS content community, use Soft Tech & Scientific Pastels. Do not use Nature/Science/Cell biomedical graphical abstract styling, hand-drawn, photorealistic, heavy 3D, shadow-heavy, glossy marketing poster, or dashboard-collage styles.

Critical text constraints:
{VISIBLE_TEXT_RULE}

Internal layout headings such as "ZONE", "LAYOUT CONFIGURATION", "Input", "Output", or "Container" may be used in this prompt to organize instructions, but they must not appear as visible text inside the rendered figure unless they are explicitly included in the visible-text list above.

Translate the following structural blueprint into the final image:

[Paste the full Visual Schema here]
```

## Materials and chemistry

Use for materials mechanisms, electrochemistry, catalysis, crystal/interface figures, molecular structures, ion migration, reaction pathways, and multiscale material schematics.

### Stage 1: Visual Schema

```markdown
# Role
你是一位 Nature Materials / Advanced Materials 风格的科学可视化架构师。你的核心能力是将材料与化学论文中的结构机制与反应路径，转化为具体的、结构化的、物理可实现的视觉指令。

# Objective
阅读我提供的材料或化学论文内容，输出一份 [VISUAL SCHEMA]。这份 Schema 将被直接发送给 AI 绘图模型，因此必须使用严格的物理结构描述与空间指令。

# Phase 1: Layout Strategy Selector
从以下布局原型中选择最合适的一个或组合：
1. Reaction Pathway Linear Flow: 左到右反应路径。
2. Solvation or Coordination Cyclic Model: 中心为配位或溶剂化结构，周围为离子分布。
3. Hierarchical Multiscale Structure: 宏观器件到微观结构到原子级结构。
4. Parallel Material Comparison: 左右或上下对比不同材料体系或条件。
5. Core-Shell / Interface Hub Model: 中心为纳米颗粒或晶体核心，外层为壳层或界面结构。

# Phase 2: Schema Generation Rules
1. Dynamic Zoning: 定义 2-5 个明确空间区域。
2. Internal Visualization: 每个区域必须包含具体材料结构对象，例如球棍分子、晶格单元、层状结构、溶剂化壳层、界面膜、离子球。
3. Explicit Connections: 明确离子迁移、电荷流向、反应方向、扩散路径或氧化还原循环。

# Output Format
---BEGIN PROMPT---

[Style & Meta-Instructions]
High-fidelity materials science schematic, professional academic illustration for materials or chemistry journals. Clean white background, strictly 2D vector style, no photorealism, no shadow, no perspective distortion. Subtle isometric alignment allowed only for crystal lattices.

[LAYOUT CONFIGURATION]
* Selected Layout: [...]
* Composition Logic: [...]
* Color Palette: Low-saturation scientific palette with clear element distinction.

[ZONE 1: LOCATION - LABEL]
* Container: [...]
* Visual Structure: [...]
* Key Text Labels: "[Label 1]"

[ZONE 2: LOCATION - LABEL]
* Container: [...]
* Visual Structure: [...]
* Key Text Labels: "[Label 2]"

[CONNECTIONS]
1. [...]
2. [...]

---END PROMPT---

# Input Data
[Insert extracted research context]
```

### Stage 2: Rendering prompt

```markdown
Generate a professional materials science mechanism schematic suitable for a top-tier materials or chemistry journal.

Visuals: strict flat vector illustration, clean geometric shapes, molecular ball-and-stick models, periodic crystal lattice arrays, thin outlines, soft pastel scientific color coding, clean white background. Interfaces must be represented as flat planar boundaries. Reaction arrows must be directional and physically interpretable.

Critical text constraints:
{VISIBLE_TEXT_RULE}

Internal layout headings such as "ZONE", "LAYOUT", or "Container" may be used in this prompt to organize instructions, but they must not appear as visible text inside the rendered figure unless they are explicitly included in the visible-text list above.

Translate the following structural blueprint into the final image:

[Paste the full Visual Schema here]
```

## Biology and medicine

Use for signaling pathways, disease mechanisms, drug mechanisms, clinical trial flow, cell microenvironment figures, and biological graphical abstracts.

### Stage 1: Visual Schema

```markdown
# Role
你是一位 Nature/Cell/Science 风格的资深医学插画师。你的核心能力是将复杂的生物医学机制、临床试验设计或分子通路转化为直观的、符合生物学特征的、出版级视觉指令。

# Objective
阅读我提供的论文或摘要内容，输出一份 [VISUAL SCHEMA]。这份 Schema 将被直接发送给 AI 绘图模型，因此必须使用精确的生物实体描述，而非抽象几何形状。

# Phase 1: Layout Strategy Selector
从以下生物医学布局原型中选择最合适的一个或组合：
1. Signaling Pathway: 上下或左右级联通路。
2. Cyclic/Regulatory Loop: 反馈调节或复制周期。
3. Anatomical/Spatial Zoom: 器官到组织到细胞到分子的跨尺度展示。
4. Comparative/Parallel Groups: 对照组、治疗组、突变组等平行比较。
5. Interaction Network: 核心分子连接周围多靶点。

# Phase 2: Schema Generation Rules
1. Biological Context: 定义背景环境，例如 cytosol, nucleus, synaptic cleft, blood vessel, tissue, Petri dish。
2. Entity Materialization: Gene 用 double helix segment，protein 用 folded structure，cell 用 lipid bilayer sphere with receptors。不要用抽象方块代表生物实体。
3. Bio-Semantics in Connections: Arrow tip 表示激活，flat tip 表示抑制，dotted arrow 表示易位、运输或分泌。

# Output Format
---BEGIN PROMPT---

[Style & Meta-Instructions]
High-fidelity scientific illustration, BioRender-style medical illustration, smooth organic forms, clean white background, high resolution 4k, distinct cellular compartments.

[LAYOUT CONFIGURATION]
* Selected Layout: [...]
* Composition Logic: [...]
* Color Palette: Biomimetic and distinct, with contrast for key molecules.

[ZONE 1: LOCATION - CONTEXT]
* Container: [...]
* Visual Structure: [...]
* Key Text Labels: "[Label 1]", "[Label 2]"

[ZONE 2: LOCATION - CONTEXT]
* Container: [...]
* Visual Structure: [...]
* Key Text Labels: "[Label 3]"

[CONNECTIONS & INTERACTIONS]
1. [...]
2. [...]

---END PROMPT---

# Input Data
[Insert extracted research context]
```

### Stage 2: Rendering prompt

```markdown
Generate a standard biological pathway or medical mechanism diagram suitable for a Cell/Nature-style figure.

Visuals: clean vector-like medical illustration with smooth organic forms, professional biological pastel palette, white background, clear compartments, readable dark labels on light backgrounds. Use rounded biological forms rather than sharp abstract blocks.

Critical text constraints:
{VISIBLE_TEXT_RULE}

Internal layout headings such as "ZONE", "LAYOUT", or "Container" may be used in this prompt to organize instructions, but they must not appear as visible text inside the rendered figure unless they are explicitly included in the visible-text list above.

Translate the following structural blueprint into the final image:

[Paste the full Visual Schema here]
```
