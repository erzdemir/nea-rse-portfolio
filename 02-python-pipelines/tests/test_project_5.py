import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "pipeline"))
from run_pipeline import main


def test_pipeline():
    rc = main(["--skip-cpp", "--db", str(ROOT / "data" / "test_pipeline.sqlite")])
    assert rc == 0


if __name__ == "__main__":
    test_pipeline()
    print("project 5 ok")
