# C++ toolkit — five interview projects

| # | Binary | Role |
|---|---|---|
| 1 | xs_lookup | Pointwise lookup |
| 2 | xs_compare | Compare two evaluations |
| 3 | tape_audit | Required MAT/MF/MT/T |
| 4 | xs_condense | Pointwise to groups |
| 5 | process_pipeline | Tape to JSON audit |

Build:
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build
  ctest --test-dir build --output-on-failure

Project 5 demo:
  ./build/process_pipeline --tape data/pipeline.tape

Not official JEFF/ENDF. Not NJOY/JANIS.
