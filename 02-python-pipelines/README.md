# Python pipelines — five interview projects

| # | Program | Role |
|---|---|---|
| 1 | pipeline/endf_ingest.py | Required MAT/MF/MT/T |
| 2 | pipeline/eval_compare.py | Compare two tables |
| 3 | pipeline/group_condense.py | Pointwise to groups |
| 4 | pipeline/catalogue.py | SQLite audit store |
| 5 | pipeline/run_pipeline.py | Orchestrate 1+4 and optional C++ |

Project 5:
  python pipeline/run_pipeline.py --skip-cpp
  python pipeline/run_pipeline.py

The second form calls C++ process_pipeline if
01-cpp-scientific/build/process_pipeline exists.

Do not commit data/*.sqlite or data/audit.json.
