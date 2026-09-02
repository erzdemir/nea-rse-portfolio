# Python pipelines — five interview projects

| # | Program | Status | Role |
|---|---|---|---|
| 1 | pipeline/endf_ingest.py | done | Required MAT/MF/MT/T |
| 2 | pipeline/eval_compare.py | done | Compare two tables |
| 3 | pipeline/group_condense.py | done | Pointwise to groups |
| 4 | catalogue.py | next | SQLite audit store |
| 5 | run_pipeline.py | next | Orchestrate + optional C++ |

Project 3:
  python pipeline/group_condense.py --table data/u235_jeff_synthetic.csv --groups data/groups_4.csv
