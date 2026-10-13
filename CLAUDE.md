# CPU Gaussian Splatting Renderer — CS 4361 Final Project

Team: Dhruv Sharma, Prateek Banda, Rishabh Sabnavis, Orvin Ahmed. Due Dec 1, 2026.

## What this is
A CPU-only renderer for pretrained 3D Gaussian Splatting scenes (Kerbl et al., SIGGRAPH 2023).
No GPU, no CUDA, no OpenGL, no paid services. We render existing .ply scenes; we do NOT train.

Pipeline (`src/renderer.cpp`):
1. Project each Gaussian to a 2D ellipse (`math.cpp`) — Sigma' = J W Sigma W^T J^T
2. View-dependent color from spherical harmonics (`sh.cpp`)
3. Bin splats into 16x16 tiles and depth-sort each tile (`tiles.cpp`)
4. Front-to-back alpha blending per pixel, tiles in parallel with OpenMP (`renderer.cpp`)

## Build and run
```
cmake -S . -B build && cmake --build build -j
./build/gs_render --test-scene -o out/test.png
./build/gs_tests
```
Dependencies (GLM, happly, stb) download automatically via CMake FetchContent.
OpenMP is optional (faster if found). SDL2 is only needed for `gs_preview`.

## Ownership (each person owns their files)
- Dhruv: `include/gs/gaussian.h`, `math.*`, blending in `renderer.cpp`, integration
- Prateek: `tiles.*`, threading and performance in `renderer.cpp`
- Rishabh: `ply_loader.*`, `sh.*`, `trim.*`
- Orvin: `apps/preview_main.cpp`, `turntablePath` in `camera.cpp`, `scripts/`

Unfinished work is marked `TODO(Name)` with the exact steps. Search with `grep -rn "TODO(" src apps`.

## Rules for Claude Code in this repo
- Keep the public interfaces in `include/gs/` stable; if one must change, say so explicitly.
- C++17, no new dependencies without asking. Never add GPU code (OpenGL, CUDA, Vulkan).
- Match the reference implementation's conventions (SH constants, +0.5 color offset,
  0.3 low-pass on the 2D covariance, alpha clamp at 0.99, 1/255 alpha cutoff).
- GLM is column-major: `m[col][row]`. Double-check matrix indexing.
- After a change: build, run `./build/gs_tests`, and render the test scene to check the image.
- Team members must be able to explain their own code in the final presentation,
  so explain the math when implementing it rather than just writing it.
