import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "pipeline"))

from endf_ingest import BusinessLogicError, main, parse_tape


def test_good_tape():
    text = (ROOT / "pipeline" / "sample_tape.txt").read_text(encoding="utf-8")
    records = parse_tape(text, "sample_tape.txt")
    assert len(records) == 2
    assert records[0].material_id == "U235"
    assert records[0].mt == 18
    assert records[1].mt == 102


def test_bad_tape():
    text = (ROOT / "pipeline" / "bad_tape.txt").read_text(encoding="utf-8")
    try:
        parse_tape(text, "bad_tape.txt")
    except BusinessLogicError as exc:
        assert "refusing to guess" in str(exc)
        return
    raise AssertionError("bad tape should fail")


def test_cli_good():
    assert main(["--tape", str(ROOT / "pipeline" / "sample_tape.txt")]) == 0


if __name__ == "__main__":
    test_good_tape()
    test_bad_tape()
    test_cli_good()
    print("all tests passed")
