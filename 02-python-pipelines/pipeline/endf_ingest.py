"""Nuclear-data ingest with explicit business-logic guards.

Job mapping
  Integrated pipelines; collection and management of nuclear physics data;
  consistency of business logic.

A real Data Bank path would next call NJOY or FRENDY. This script only
accepts or rejects the identifiers those codes must not guess.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import asdict, dataclass
from pathlib import Path

CONTROL_RE = re.compile(
    r"^MAT=(?P<mat>\S+)\s+MF=(?P<mf>\d+)\s+MT=(?P<mt>\d+)\s+T=(?P<temp>[\d.]+)\s*$"
)


class BusinessLogicError(ValueError):
    """Input violated a declared nuclear-data contract."""


@dataclass(frozen=True)
class AuditRecord:
    source_name: str
    material_id: str
    mf: int
    mt: int
    temperature_k: float
    processor: str
    status: str


def parse_tape(text: str, source_name: str) -> list[AuditRecord]:
    records: list[AuditRecord] = []
    for raw in text.splitlines():
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        match = CONTROL_RE.match(line)
        if not match:
            raise BusinessLogicError(
                f"{source_name}: missing MAT=/MF=/MT=/T= (refusing to guess identifiers): {line}"
            )
        records.append(
            AuditRecord(
                source_name=source_name,
                material_id=match.group("mat"),
                mf=int(match.group("mf")),
                mt=int(match.group("mt")),
                temperature_k=float(match.group("temp")),
                processor="synthetic-ingest/0.2",
                status="accepted",
            )
        )
    if not records:
        raise BusinessLogicError(f"{source_name}: tape contains no control cards")
    return records


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Validate a synthetic nuclear-data tape.")
    parser.add_argument("--tape", required=True, help="Path to the control-card file")
    args = parser.parse_args(argv)
    path = Path(args.tape)
    try:
        records = parse_tape(path.read_text(encoding="utf-8"), path.name)
    except (OSError, BusinessLogicError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    print(json.dumps([asdict(item) for item in records], indent=2))
    return 0


if __name__ == "__main__":
    sys.exit(main())
