# C++ projects — spoken notes

## Project 1 — xs_lookup
Typed table. Declared interpolation. No silent extrapolation.

## Project 2 — xs_compare
JANIS-shaped question: two evaluations, one query grid, one tolerance.
The tolerance is the business rule. Change it, and the accepted answer changes.

Live demo:
  ./build/xs_compare --a data/u235_jeff_synthetic.csv --b data/u235_endf_synthetic.csv --tol 0.02
  Exit code 1 is the demo: the libraries differ by more than 2 percent.
  ./build/xs_compare --a data/u235_jeff_synthetic.csv --b data/u235_endf_synthetic.csv --tol 0.20
  Same numbers, now accepted.

Sentence:
  I have used JANIS on JEFF, ENDF and EXFOR. I did not write JANIS.
  This C++ tool is how I would characterise two processed products
  before a service migration.

## Projects 3-5
Tape audit, group condensation, then a pipeline that calls 1-4.
