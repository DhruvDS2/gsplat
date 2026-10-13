#!/usr/bin/env python3
"""Render time vs thread count. Owner: Orvin (with Prateek).

Usage:
    python scripts/benchmark.py --ply scenes/garden/point_cloud.ply --threads 1 2 4 8 --runs 3
"""
import argparse
import re
import subprocess
import sys

TOTAL_RE = re.compile(r"total=([\d.]+)ms")


def main() -> int:
    p = argparse.ArgumentParser()
    p.add_argument("--exe", default="build/gs_render")
    p.add_argument("--ply", default=None, help="omit to use the built-in test scene")
    p.add_argument("--threads", type=int, nargs="+", default=[1, 2, 4, 8])
    p.add_argument("--runs", type=int, default=3)
    args = p.parse_args()

    scene_args = ["--ply", args.ply] if args.ply else ["--test-scene"]
    print("threads,mean_ms")
    for t in args.threads:
        times = []
        for _ in range(args.runs):
            out = subprocess.run([args.exe, *scene_args, "--threads", str(t), "-o", "out/bench.png"],
                                 capture_output=True, text=True, check=True).stdout
            m = TOTAL_RE.search(out)
            if m:
                times.append(float(m.group(1)))
        print(f"{t},{sum(times) / len(times):.1f}" if times else f"{t},n/a")
    return 0


if __name__ == "__main__":
    sys.exit(main())
