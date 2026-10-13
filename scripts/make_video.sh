#!/usr/bin/env bash
# Turn rendered frames into an MP4. Owner: Orvin.
# Usage: scripts/make_video.sh out/frames out/turntable.mp4 [fps]
set -euo pipefail
FRAMES=${1:-out/frames}
OUT=${2:-out/turntable.mp4}
FPS=${3:-30}
ffmpeg -y -framerate "$FPS" -i "$FRAMES/frame_%04d.png" -c:v libx264 -pix_fmt yuv420p "$OUT"
echo "Wrote $OUT"
