"""Python Project 2 — compare two synthetic evaluations.

Same question as C++ xs_compare: two tables, one query grid, one tolerance.
The tolerance is the business rule.
"""
from __future__ import annotations

import argparse
import csv
import math
import sys
from pathlib import Path


def load_table(path: Path) -> tuple[list[float], list[float]]:
    energy: list[float] = []
    xs: list[float] = []
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        e_s, x_s = [p.strip() for p in line.split(",")]
        energy.append(float(e_s))
        xs.append(float(x_s))
    if len(energy) < 2:
        raise ValueError(f"{path}: need at least two rows")
    if any(energy[i] <= energy[i - 1] for i in range(1, len(energy))):
        raise ValueError(f"{path}: energy grid must increase")
    return energy, xs


def lookup_loglog(energy: list[float], xs: list[float], e: float) -> float:
    if e < energy[0] or e > energy[-1]:
        raise ValueError(f"energy {e} outside table (no silent extrapolation)")
    lo = 0
    hi = len(energy) - 1
    if e == energy[0]:
        return xs[0]
    for i in range(1, len(energy)):
        if energy[i] >= e:
            lo, hi = i - 1, i
            break
    t = math.log(e / energy[lo]) / math.log(energy[hi] / energy[lo])
    return xs[lo] * (xs[hi] / xs[lo]) ** t


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--a", required=True)
    parser.add_argument("--b", required=True)
    parser.add_argument("--tol", type=float, default=0.02)
    parser.add_argument("--energy", type=float, action="append")
    args = parser.parse_args(argv)
    queries = args.energy or [0.0253, 1.0, 1.0e3]
    try:
        ea, xa = load_table(Path(args.a))
        eb, xb = load_table(Path(args.b))
        max_abs = 0.0
        print(f"a={args.a}")
        print(f"b={args.b}")
        print(f"tolerance={args.tol}")
        for e in queries:
            sa = lookup_loglog(ea, xa, e)
            sb = lookup_loglog(eb, xb, e)
            if sa == 0.0:
                raise ValueError("reference xs is zero")
            rel = (sb - sa) / sa
            max_abs = max(max_abs, abs(rel))
            print(f"E={e} xs_a={sa} xs_b={sb} rel_diff={rel}")
        ok = max_abs <= args.tol
        print(f"max_abs_rel_diff={max_abs}")
        print(f"within_tolerance={str(ok).lower()}")
        return 0 if ok else 1
    except (OSError, ValueError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
