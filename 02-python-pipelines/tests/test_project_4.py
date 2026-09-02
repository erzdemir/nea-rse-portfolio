import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "pipeline"))
from catalogue import connect, ingest_json, list_rows


def test_catalogue(tmp_path: Path | None = None):
    db = (tmp_path or Path("data")) / "test_catalogue.sqlite"
    if tmp_path is None:
        db = ROOT / "data" / "test_catalogue.sqlite"
        db.parent.mkdir(parents=True, exist_ok=True)
        if db.exists():
            db.unlink()
    conn = connect(db)
    n = ingest_json(conn, [{
        "source_name": "sample_tape.txt",
        "material_id": "U235",
        "mf": 3,
        "mt": 18,
        "temperature_k": 293.6,
        "processor": "python-ingest/0.2",
        "status": "accepted",
    }])
    assert n == 1
    rows = list_rows(conn)
    assert rows[0]["mt"] == 18
    conn.close()
    print("project 4 ok")


if __name__ == "__main__":
    test_catalogue()
