# C++ toolkit — five interview projects

| # | Binary | Status | Role |
|---|---|---|---|
| 1 | xs_lookup | done | Pointwise lookup |
| 2 | xs_compare | done | Compare two evaluations |
| 3 | tape_audit | done | Required MAT/MF/MT/T |
| 4 | xs_condense | done | Pointwise to groups |
| 5 | process_pipeline | next | Tape to audit record |

Build:
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build

Project 4 demo:
  ./build/xs_condense --table data/u235_jeff_synthetic.csv --groups data/groups_4.csv --law log-log
