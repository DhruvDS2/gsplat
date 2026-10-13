# CPU Gaussian Splatting Renderer

CS 4361.501 Computer Graphics final project, Fall 2026.
Dhruv Sharma · Prateek Banda · Rishabh Sabnavis · Orvin Ahmed

Renders pretrained 3D Gaussian Splatting scenes entirely on the CPU, in C++17.

## Setup

Needs: CMake 3.20+, a C++17 compiler, Git. Optional: OpenMP (multithreading), SDL2 (preview window), FFmpeg (videos), Python 3 with numpy + pillow (evaluation).

| OS | Install |
| --- | --- |
| Ubuntu / WSL | `sudo apt install build-essential cmake libsdl2-dev ffmpeg` |
| macOS | `brew install cmake libomp sdl2 ffmpeg` |
| Windows | Visual Studio 2022 (C++ workload) + CMake; SDL2 via vcpkg, or use WSL |

```
git clone <repo-url> && cd gsplat
cmake -S . -B build
cmake --build build -j
./build/gs_render --test-scene -o out/test.png
./build/gs_tests
```

No SDL2? Configure with `-DGS_BUILD_PREVIEW=OFF`.

## Layout

```
include/gs/   shared interfaces (everyone codes against these)
src/          implementation, one file per component
apps/         gs_render (CLI), gs_preview (SDL2 window)
tests/        unit tests
scripts/      PSNR, benchmarks, video export
scenes/       downloaded .ply scenes (not in Git, see scenes/README.md)
out/          rendered images (not in Git)
docs/         task list and notes
```

## Commands

```
./build/gs_render --ply <scene.ply> -o out/scene.png --sh 3 --threads 8
./build/gs_render --ply <scene.ply> --trim 0.05 -o out/trimmed.png
./build/gs_render --ply <scene.ply> --turntable 120 -o out/frames
scripts/make_video.sh out/frames out/turntable.mp4
python scripts/psnr.py out/scene.png reference.png
python scripts/benchmark.py --ply <scene.ply> --threads 1 2 4 8
./build/gs_preview --ply <scene.ply>
```

See `docs/TASKS.md` for who is doing what and when.
