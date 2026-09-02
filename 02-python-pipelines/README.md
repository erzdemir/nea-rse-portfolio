# Python pipelines — five interview projects

| # | Program | Status | Role |
|---|---|---|---|
| 1 | pipeline/endf_ingest.py | done | Required MAT/MF/MT/T |
| 2 | pipeline/eval_compare.py | done | Compare two tables |
| 3 | group_condense.py | next | Pointwise to groups |
| 4 | catalogue.py | next | SQLite audit store |
| 5 | run_pipeline.py | next | Orchestrate + optional C++ |

Project 1:
  python pipeline/endf_ingest.py --tape pipeline/sample_tape.txt
  python pipeline/endf_ingest.py --tape pipeline/bad_tape.txt

Project 2:
  python pipeline/eval_compare.py --a data/u235_jeff_synthetic.csv --b data/u235_endf_synthetic.csv --tol 0.02
  python pipeline/eval_compare.py --a data/u235_jeff_synthetic.csv --b data/u235_endf_synthetic.csv --tol 0.20

Tests:
  python tests/test_projects_1_2.py
