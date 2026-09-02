# 01 — C++ / Fortran scientific computing

**Vacancy line:** *Strong expertise with one or multiple software languages used in scientific computing (C++, Fortran, Python etc.)*

## What I would say in the interview

I do not treat C++ and Fortran as interchangeable “coding skills”. In nuclear work they occupy different layers:

- **Fortran** is still the language of record for large physics kernels, NJOY-class processing, and many reactor / CFD codes. I have used it on Linux HPC to build and extend simulation frameworks and physics-based digital twins.
- **C++** is the language I use when the same physics must live next to modern memory management, typed interfaces, and long-term maintainability.
- **Python** (folder 02) sits above both as the orchestration and data-contract layer.

The Data Bank problem is not “rewrite everything in one language”. It is: keep a validated kernel correct, expose it through a stable interface, and let pipelines and services evolve without silently changing answers.

## Experience this folder represents

- CFD / thermal-hydraulic and digital-twin frameworks in C++ and Fortran on Linux HPC (University of Tokyo / project research).
- Nuclear data processing workflows that consume and emit numeric tables (cross sections, group structures) where bit-level reproducibility matters.
- The vacancy’s “exploratory research code **and** production-quality software” split: a kernel starts as a research experiment and must later be callable from a pipeline without hidden flags.

## Artefact

`src/xs_lookup.cpp` is a small, testable C++17 kernel:

- loads a tiny synthetic pointwise cross-section table (energy, xs)
- interpolates in lethargy / log-log (the interpolation nuclear data people actually argue about)
- fails loudly on unsorted or non-positive grids (business-logic guard)
- can be wrapped later by Python (`pybind11`) or called from a container

This is deliberately small. In interview, use it to talk about:

1. numeric contracts (units, interpolation law, temperature)
2. why silent extrapolation is unacceptable for a Data Bank service
3. how I would put a Fortran NJOY/FRENDY step behind the same contract

## How I would grow this at the Data Bank

- Wrap validated Fortran processing (NJOY/FRENDY) as a versioned CLI, not as a copied subroutine.
- Add a golden-file test: same ENDF tape + same NJOY input deck → same ACE digest.
- Publish the digest, not the licensed library, through the service API.
