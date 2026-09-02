# C++ toolkit — five interview projects

All programs share the Project 1 library `nea::XsTable`.

| # | Binary | Role |
|---|---|---|
| 1 | xs_lookup | Pointwise lookup, no silent extrapolation |
| 2 | xs_compare | Compare two synthetic evaluations |
| 3 | tape_audit | (next) required MAT/MF/MT/T cards |
| 4 | xs_condense | (next) pointwise to energy groups |
| 5 | process_pipeline | (next) tape to fingerprint |

Build:
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build

Project 2 demo:
  ./build/xs_compare --a data/u235_jeff_synthetic.csv --b data/u235_endf_synthetic.csv --tol 0.02
  ./build/xs_compare --a data/u235_jeff_synthetic.csv --b data/u235_endf_synthetic.csv --tol 0.20

Not official JEFF/ENDF data. Not JANIS.
