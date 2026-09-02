import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "pipeline"))

from endf_ingest import BusinessLogicError, parse_tape
from eval_compare import main as compare_main


def test_ingest():
    text = (ROOT / "pipeline" / "sample_tape.txt").read_text(encoding="utf-8")
    rec = parse_tape(text, "sample_tape.txt")
    assert rec[0].mt == 18 and rec[1].mt == 102
    bad = (ROOT / "pipeline" / "bad_tape.txt").read_text(encoding="utf-8")
    try:
        parse_tape(bad, "bad_tape.txt")
    except BusinessLogicError:
        return
    raise AssertionError("bad tape should fail")


def test_compare():
    a = str(ROOT / "data" / "u235_jeff_synthetic.csv")
    b = str(ROOT / "data" / "u235_endf_synthetic.csv")
    assert compare_main(["--a", a, "--b", b, "--tol", "0.02"]) == 1
    assert compare_main(["--a", a, "--b", b, "--tol", "0.20"]) == 0


if __name__ == "__main__":
    test_ingest()
    test_compare()
    print("all tests passed")
