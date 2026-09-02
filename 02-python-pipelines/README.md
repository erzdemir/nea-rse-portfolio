# 02 — Python data pipelines and business logic

**Vacancy line:** create software and DevOps solutions with *integrated pipelines*; create frameworks for collection, storage and management of nuclear physics data and experimental benchmarks.

## What I would say in the interview

Python is how I turn a validated nuclear-data step into a service other people can run without inheriting my laptop. The important part is not the library list. It is the **contract**:

- isolate **performance metrics** from auxiliary inputs
- reject files that do not satisfy the declared format / MAT / MF / MT expectations
- write an audit record of *which evaluation, which processor version, which interpolation, which temperature*
- make the happy path boring and the failure path loud

That language is already on my CV because it is how I had to work with ENDF/JEFF tapes, EXFOR comparisons, and experimental benchmark collections (including aerosol-deposition datasets).

## Experience this folder represents

- Scalable Python ingestion for high-velocity scientific data
- Modular scripts that enforce syntax and business-logic validation
- Frameworks for nuclear-energy application data and experimental benchmarks
- Google Data Analytics Professional Certificate (SQL, Python, R) as supporting literacy, not as the nuclear-data skill

## Artefact

`pipeline/endf_ingest.py` is a deliberately small validator:

- reads a *synthetic* ENDF-like tape header
- extracts material / file / reaction identifiers
- refuses to continue if required control cards are missing
- emits a JSON audit record a downstream SQL/Invenio layer can store

Talking point: this is the same discipline I would apply when wrapping NJOY or FRENDY in a Data Bank pipeline so that a JEFF file processed in 2026 can still be reconstructed in 2032.

## How this maps to Data Bank work

JEFF official releases already live on the **NEA GitLab**, with pipelines in the local datacentre. A Research Software Engineer does not “add Python”. They make the processing, validation and publication path **reproducible and supportable**.
