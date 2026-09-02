# Python toolkit — five projects (spoken notes)

## 1 endf_ingest
Required identifiers. Same rule as C++ tape_audit.

## 2 eval_compare
Two tables, one tolerance. Same question as C++ xs_compare.

## 3 group_condense
Pointwise to groups. Same contract as C++ xs_condense.

## 4 catalogue
SQL holds identifiers and ingest status. Not the ACE bytes.

## 5 run_pipeline
Production shape in Python: ingest -> JSON -> SQLite.
If the C++ pipeline is built, call it too.

Live demo:
  python pipeline/run_pipeline.py --skip-cpp

Sentence:
  Python orchestrates and stores the audit.
  C++ freezes the numeric contract.
  NJOY/FRENDY remain the physics processors.
  That is the Data Bank split I would implement.
