# C++ toolkit — five interview projects

| # | Binary | Status | Role |
|---|---|---|---|
| 1 | xs_lookup | done | Pointwise lookup |
| 2 | xs_compare | done | Compare two evaluations |
| 3 | tape_audit | done | Required MAT/MF/MT/T |
| 4 | xs_condense | next | Pointwise to groups |
| 5 | process_pipeline | next | Tape to fingerprint |

Build:
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build

Project 3 demo:
  ./build/tape_audit --tape data/sample.tape
  ./build/tape_audit --tape data/bad.tape
