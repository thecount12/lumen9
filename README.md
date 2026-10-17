# lumen


lumen9 (Inference Runtime)
  ┌────────────────────────────────────────────────────────┐
  │  - The official weight loader, token loop, and graph  │
  │  - Manages KV-caches & autoregressive text generation  │
  └──────────────┬──────────────────────────┬──────────────┘
                 │ Compiles scripts with    │ Executes math on
                 ▼                          ▼
            lux (Compiler)           flux9 (Compute Tile)
```


The Blueprinted Mandate for lumen9

lumen9 should be an incredibly tight, streamlined repository containing only three core architectural files written in pureC. It acts as the glue code that loads files from disk and drives the flux9 machine loop:

1. loader.c (Deterministic Weight Streaming)

This file avoids heavy file system structures. It maps your weights (.bin) straight into fixed RAM pointer structures. It takes a raw file from your network grid or host disk, verifies the dimensions, and slices it into sequential arrays that match the increase-matrix stride layout of flux9.

2. tokenizer.c (Minimal Byte/Word Mapping)

This handles ingestion. It reads a prompt string, matches it against a packed token file structure, and emits a clean integer array of token IDs directly to your model's input vector slot.

3. main.c (The Autoregressive Loop Engine)

The beating heart of inference. This is the top-level orchestrator loop. It handles the state machine of text generation. Its structure is purely linear and non-blocking:



