"""Python Project 3 — condense a pointwise table into energy groups.

Same contract as C++ xs_condense:
  declared group bounds, lethargy average, no silent fill of empty groups.
This is not NJOY GROUPR.
"""
from __future__ import annotations

import argparse
import math
import sys
from pathlib import Path


def load_xy(path: Path) -> tuple[list[float], list[float]]:
    x: list[float] = []
    y: list[float] = []
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        left, right = [p.strip() for p in line.replace(",", " ").split()[:2]]
        x.append(float(left))
        y.append(float(right))
    if len(x) < 2:
        raise ValueError(f"{path}: need at least two rows")
    if any(x[i] <= x[i - 1] for i in range(1, len(x))):
        raise ValueError(f"{path}: values must increase")
    return x, y


def lookup_loglog(energy: list[float], xs: list[float], e: float) -> float:
    if e < energy[0] or e > energy[-1]:
        raise ValueError(f"energy {e} outside table (no silent extrapolation)")
    if e == energy[0]:
        return xs[0]
    for i in range(1, len(energy)):
        if energy[i] >= e:
            lo, hi = i - 1, i
            t = math.log(e / energy[lo]) / math.log(energy[hi] / energy[lo])
            return xs[lo] * (xs[hi] / xs[lo]) ** t
    return xs[-1]


def lethargy_average(energy: list[float], xs: list[float], e0: float, e1: float) -> float:
    nseg = 8
    u0, u1 = math.log(e0), math.log(e1)
    du = (u1 - u0) / nseg
    acc = 0.0
    xs_prev = lookup_loglog(energy, xs, e0)
    for i in range(1, nseg + 1):
        e = math.exp(u0 + du * i)
        xs_now = lookup_loglog(energy, xs, e)
        acc += 0.5 * (xs_prev + xs_now) * du
        xs_prev = xs_now
    return acc / (u1 - u0)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--table", required=True)
    parser.add_argument("--groups", required=True)
    args = parser.parse_args(argv)
    try:
        energy, xs = load_xy(Path(args.table))
        bounds, _ = load_xy(Path(args.groups))
        print(f"pointwise_n={len(energy)}")
        print("energy_eV,xs_barn")
        n_out = 0
        for i in range(1, len(bounds)):
            lo = max(bounds[i - 1], energy[0])
            hi = min(bounds[i], energy[-1])
            if not (hi > lo and lo > 0.0):
                continue
            print(f"{hi},{lethargy_average(energy, xs, lo, hi)}")
            n_out += 1
        if n_out < 2:
            raise ValueError("condensation produced fewer than two groups")
        print(f"groups_n={n_out}")
        return 0
    except (OSError, ValueError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
