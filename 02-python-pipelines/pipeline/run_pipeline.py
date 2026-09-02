"""Python Project 5 — orchestrate ingest + catalogue, optionally call C++.

Job mapping
  Integrated pipelines; exploratory research code AND production software.
  Python records identifiers and writes the audit.
  C++ process_pipeline is used when the binary has been built.

This script does not guess MAT/MF/MT/T. It calls Project 1, then Project 4.
"""
from __future__ import annotations

import argparse
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REPO = ROOT.parent
INGEST = ROOT / "pipeline" / "endf_ingest.py"
CATALOGUE = ROOT / "pipeline" / "catalogue.py"
TAPE = ROOT / "pipeline" / "sample_tape.txt"
CPP_BIN_WIN = REPO / "01-cpp-scientific" / "build" / "process_pipeline.exe"
CPP_BIN_UNIX = REPO / "01-cpp-scientific" / "build" / "process_pipeline"
CPP_TAPE = REPO / "01-cpp-scientific" / "data" / "pipeline.tape"


def run_python(script: Path, args: list[str]) -> subprocess.CompletedProcess[str]:
    cmd = [sys.executable, str(script), *args]
    return subprocess.run(cmd, check=False, capture_output=True, text=True)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--tape", default=str(TAPE))
    parser.add_argument("--db", default=str(ROOT / "data" / "catalogue.sqlite"))
    parser.add_argument("--skip-cpp", action="store_true")
    args = parser.parse_args(argv)

    audit_path = ROOT / "data" / "audit.json"
    audit_path.parent.mkdir(parents=True, exist_ok=True)

    ingest = run_python(INGEST, ["--tape", args.tape])
    if ingest.returncode != 0:
        print(ingest.stderr, file=sys.stderr)
        return ingest.returncode
    audit_path.write_text(ingest.stdout, encoding="utf-8")
    print("ingest=ok")

    loaded = run_python(CATALOGUE, ["--db", args.db, "--load-json", str(audit_path)])
    if loaded.returncode != 0:
        print(loaded.stderr, file=sys.stderr)
        return loaded.returncode
    print(loaded.stdout.strip())

    listed = run_python(CATALOGUE, ["--db", args.db, "--list"])
    print("catalogue=")
    print(listed.stdout)

    cpp = CPP_BIN_WIN if CPP_BIN_WIN.exists() else CPP_BIN_UNIX
    if args.skip_cpp or not cpp.exists() or not CPP_TAPE.exists():
        print("cpp_pipeline=skipped")
        return 0

    cpp_run = subprocess.run(
        [str(cpp), "--tape", str(CPP_TAPE)],
        check=False,
        capture_output=True,
        text=True,
    )
    if cpp_run.returncode != 0:
        print(cpp_run.stderr, file=sys.stderr)
        print("cpp_pipeline=failed")
        return cpp_run.returncode
    print("cpp_pipeline=ok")
    print(cpp_run.stdout)
    return 0


if __name__ == "__main__":
    sys.exit(main())
