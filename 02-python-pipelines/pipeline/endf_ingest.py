"""Synthetic ENDF-like ingest with explicit business-logic guards.

Interview artefact only. Does not parse real ENDF-6 tapes.
"""

from __future__ import annotations

import json
import re
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import List


class BusinessLogicError(ValueError):
    """Raised when an input violates a declared nuclear-data contract."""


@dataclass(frozen=True)
class AuditRecord:
    source_name: str
    material_id: str
    mf: int
    mt: int
    processor: str
    interpolation: str
    temperature_k: float
    n_control_cards: int
    status: str


CONTROL_RE = re.compile(
    r"^MAT=(?P<mat>\S+)\s+MF=(?P<mf>\d+)\s+MT=(?P<mt>\d+)\s+T=(?P<temp>[\d.]+)"
)


def parse_header(text: str, source_name: str) -> AuditRecord:
    lines = [ln.strip() for ln in text.splitlines() if ln.strip()]
    if not lines:
        raise BusinessLogicError("empty tape: no control information")

    cards: List[re.Match[str]] = []
    for ln in lines:
        if ln.startswith("#"):
            continue
        m = CONTROL_RE.match(ln)
        if m:
            cards.append(m)

    if not cards:
        raise BusinessLogicError(
            "missing required control card MAT=/MF=/MT=/T= "
            "(refusing to guess identifiers)"
        )

    first = cards[0]
    return AuditRecord(
        source_name=source_name,
        material_id=first.group("mat"),
        mf=int(first.group("mf")),
        mt=int(first.group("mt")),
        processor="synthetic-ingest/0.1",
        interpolation="log-log",
        temperature_k=float(first.group("temp")),
        n_control_cards=len(cards),
        status="accepted",
    )


def ingest(path: Path) -> str:
    record = parse_header(path.read_text(encoding="utf-8"), path.name)
    return json.dumps(asdict(record), indent=2)


if __name__ == "__main__":
    sample = Path(__file__).with_name("sample_tape.txt")
    print(ingest(sample))
