"""Python Project 4 — SQLite catalogue for nuclear-data audit records.

Job mapping
  SQL datastores; frameworks for collection and storage of nuclear physics data.
  Identifiers, versions and ingest status belong in SQL.
  The bulky ACE/ENDF bytes would live in object storage, not in this database.

This is not InvenioRDM. Project 5 / the Invenio folder maps records onto that
platform. This file is the relational core a Data Bank catalogue can grow from.
"""
from __future__ import annotations

import argparse
import json
import sqlite3
import sys
from pathlib import Path

SCHEMA = """
CREATE TABLE IF NOT EXISTS ingest_audit (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    source_name TEXT NOT NULL,
    material_id TEXT NOT NULL,
    mf INTEGER NOT NULL,
    mt INTEGER NOT NULL,
    temperature_k REAL NOT NULL,
    processor TEXT NOT NULL,
    status TEXT NOT NULL,
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);
CREATE UNIQUE INDEX IF NOT EXISTS ingest_key
    ON ingest_audit (material_id, mf, mt, temperature_k, source_name);
"""


def connect(db_path: Path) -> sqlite3.Connection:
    db_path.parent.mkdir(parents=True, exist_ok=True)
    conn = sqlite3.connect(db_path)
    conn.row_factory = sqlite3.Row
    conn.executescript(SCHEMA)
    return conn


def ingest_json(conn: sqlite3.Connection, payload: list[dict]) -> int:
    n = 0
    for row in payload:
        conn.execute(
            """
            INSERT OR REPLACE INTO ingest_audit
                (source_name, material_id, mf, mt, temperature_k, processor, status)
            VALUES (:source_name, :material_id, :mf, :mt, :temperature_k, :processor, :status)
            """,
            row,
        )
        n += 1
    conn.commit()
    return n


def list_rows(conn: sqlite3.Connection) -> list[dict]:
    cur = conn.execute(
        "SELECT material_id, mf, mt, temperature_k, status, source_name FROM ingest_audit ORDER BY id"
    )
    return [dict(r) for r in cur.fetchall()]


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--db", default="data/catalogue.sqlite")
    parser.add_argument("--load-json", help="JSON array from endf_ingest.py")
    parser.add_argument("--list", action="store_true")
    args = parser.parse_args(argv)
    try:
        conn = connect(Path(args.db))
        if args.load_json:
            payload = json.loads(Path(args.load_json).read_text(encoding="utf-8"))
            if not isinstance(payload, list):
                raise ValueError("JSON must be an array of audit records")
            n = ingest_json(conn, payload)
            print(f"loaded={n} db={args.db}")
        if args.list or not args.load_json:
            rows = list_rows(conn)
            print(json.dumps(rows, indent=2))
        conn.close()
        return 0
    except (OSError, ValueError, sqlite3.Error, json.JSONDecodeError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
