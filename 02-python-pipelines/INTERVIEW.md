# Python projects — spoken notes

## 1-3
Ingest guards, evaluation compare, group condensation.
Same contracts as C++ tape_audit, xs_compare, xs_condense.

## 4 catalogue
SQL is the system of record for identifiers and ingest status.
Load JSON from Project 1 into SQLite and list it back.

Live demo:
  python pipeline/endf_ingest.py --tape pipeline/sample_tape.txt > data/audit.json
  python pipeline/catalogue.py --db data/catalogue.sqlite --load-json data/audit.json --list

Sentence:
  InvenioRDM still needs a relational core. This table is that core.
  Files and ACE libraries do not belong in SQLite as blobs.

## 5
Orchestrator that runs 1-4 and can call the C++ pipeline.
