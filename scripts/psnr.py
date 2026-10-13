#!/usr/bin/env python3
"""PSNR between our render and a reference image. Owner: Orvin.

Usage:
    python scripts/psnr.py out/garden.png reference/garden_00000.png
    python scripts/psnr.py --dir out/frames reference/frames   # average over matching file names

Needs: pip install numpy pillow
"""
import argparse
import sys
from pathlib import Path

import numpy as np
from PIL import Image


def load(path: Path) -> np.ndarray:
    return np.asarray(Image.open(path).convert("RGB"), dtype=np.float64) / 255.0


def psnr(a: np.ndarray, b: np.ndarray) -> float:
    if a.shape != b.shape:
        raise ValueError(f"size mismatch: {a.shape} vs {b.shape}")
    mse = np.mean((a - b) ** 2)
    return float("inf") if mse == 0 else 10.0 * np.log10(1.0 / mse)


def main() -> int:
    p = argparse.ArgumentParser()
    p.add_argument("ours")
    p.add_argument("reference")
    p.add_argument("--dir", action="store_true", help="compare every matching file in two folders")
    args = p.parse_args()

    if not args.dir:
        print(f"PSNR: {psnr(load(Path(args.ours)), load(Path(args.reference))):.2f} dB")
        return 0

    scores = []
    for ours in sorted(Path(args.ours).glob("*.png")):
        ref = Path(args.reference) / ours.name
        if ref.exists():
            s = psnr(load(ours), load(ref))
            scores.append(s)
            print(f"{ours.name}: {s:.2f} dB")
    if not scores:
        print("no matching files", file=sys.stderr)
        return 1
    print(f"mean PSNR over {len(scores)} images: {np.mean(scores):.2f} dB")
    return 0


if __name__ == "__main__":
    sys.exit(main())
