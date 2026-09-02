# Python projects — spoken notes

## 1 endf_ingest
Required identifiers. Same rule as C++ tape_audit.

## 2 eval_compare
Two tables, one tolerance. Same question as C++ xs_compare.

## 3 group_condense
Pointwise to declared groups. Lethargy average. No silent zero-fill.
Same contract as C++ xs_condense. Not NJOY GROUPR.

Live demo:
  python pipeline/group_condense.py --table data/u235_jeff_synthetic.csv --groups data/groups_4.csv

## 4-5
SQLite catalogue, then an orchestrator that can also call the C++ binaries.
