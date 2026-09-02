import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "pipeline"))
from group_condense import main


def test_condense():
    rc = main([
        "--table", str(ROOT / "data" / "u235_jeff_synthetic.csv"),
        "--groups", str(ROOT / "data" / "groups_4.csv"),
    ])
    assert rc == 0


if __name__ == "__main__":
    test_condense()
    print("project 3 ok")
