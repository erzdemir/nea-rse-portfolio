# Python pipelines — five interview projects

| # | Program | Status | Role |
|---|---|---|---|
| 1 | pipeline/endf_ingest.py | done | Required MAT/MF/MT/T |
| 2 | pipeline/eval_compare.py | done | Compare two tables |
| 3 | pipeline/group_condense.py | done | Pointwise to groups |
| 4 | pipeline/catalogue.py | done | SQLite audit store |
| 5 | run_pipeline.py | next | Orchestrate + optional C++ |

Project 4 demo:
  python pipeline/endf_ingest.py --tape pipeline/sample_tape.txt > data/audit.json
  python pipeline/catalogue.py --db data/catalogue.sqlite --load-json data/audit.json
  python pipeline/catalogue.py --db data/catalogue.sqlite --list

data/*.sqlite is local only. Do not commit the database file.
