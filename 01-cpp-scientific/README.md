# Project 1 — C++ nuclear-data toolkit

Interview project for the OECD NEA Data Bank Research Software Engineer post.

C++17 kernel for pointwise cross-section lookup. Interpolation law is an
argument. Energies outside the table fail; the program does not invent a number.

This is not NJOY, FRENDY, JANIS or an official JEFF/ENDF file.

Build:
  cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
  cmake --build build
  ctest --test-dir build --output-on-failure
  ./build/xs_lookup --table data/u235_jeff_synthetic.csv --law log-log --energy 0.0253

See INTERVIEW.md for the spoken walk-through.
