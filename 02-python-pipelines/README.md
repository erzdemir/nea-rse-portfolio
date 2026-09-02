# Project 2 — Python nuclear-data ingest pipeline

Interview project for the OECD NEA Data Bank Research Software Engineer post.

Python enforces business identifiers before any processing starts.
A tape without MAT/MF/MT/T is rejected. The program does not guess.

This is not NJOY, FRENDY or a real ENDF-6 parser.

Run:
  python pipeline/endf_ingest.py --tape pipeline/sample_tape.txt
  python pipeline/endf_ingest.py --tape pipeline/bad_tape.txt
  python tests/test_ingest.py

See INTERVIEW.md for the spoken walk-through.
