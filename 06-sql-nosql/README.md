# 06 — SQL and NoSQL datastores

**Vacancy line:** *Knowledge of SQL and/or NoSQL datastores would be an advantage*

## What I would say in the interview

Nuclear data is not “one table of numbers”. It is a graph of:

- evaluations (JEFF-4.0, ENDF/B-…, JENDL-…)
- materials / nuclides
- files and reactions (MF/MT)
- processed products (PENDF, GENDF, ACE) at given T
- experimental points (EXFOR)
- benchmarks and handbooks
- software packages and their validation cases
- publications and DOIs

Relational SQL is the right system of record for identifiers, permissions, versions and audit. Document / object stores (and object storage) are the right place for the bulky, schema-flexible payloads. InvenioRDM itself follows this split: **PostgreSQL + files + search index**.

I have designed SQL-backed tracking pipelines, hold a Google Data Analytics certificate that includes SQL, and have built collection/storage frameworks for experimental benchmark and aerosol-deposition datasets.

## Artefacts

- `schema.sql` — a deliberately small relational core a Data Bank catalogue could grow from
- `examples/exfor_document.json` — why a raw EXFOR-like entry is more natural as a document
- `queries/useful.sql` — the questions I would actually run

## Design rules I would defend

1. Never store an ACE library as a row blob without a checksum and a processor version.
2. Separate **catalogue identity** (SQL) from **search** (OpenSearch) from **bytes** (object store).
3. Business keys (MAT/MF/MT/T/library) are constraints, not comments.
4. Soft-delete + provenance columns; nuclear data is cited years later.
