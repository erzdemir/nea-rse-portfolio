# 07 — Invenio Research Data Management

**Vacancy line:** *Knowledge of Invenio Research Data Management would be an advantage.*

## Honest position

I have not administered a production InvenioRDM instance. The vacancy marks this as an **advantage**, not a gate. What I *do* have is the domain objects Invenio would be asked to hold at the Data Bank, and a clear picture of why NEA adopted it.

Public record: the NEA Data Bank has launched an **Invenio-based data platform**, assigns DOIs (DataCite) to publications and data libraries, and released products such as **JEFF-4.0**. That is the system I would be helping to extend, not a generic institutional repository.

## What InvenioRDM actually is (keep this crisp)

Turn-key research data repository built on the Invenio Framework (the same family as Zenodo).

Typical stack:

- **Python / Flask** application
- **PostgreSQL** — system of record
- **OpenSearch** — discovery
- **Redis + RabbitMQ** — cache and background tasks
- **object storage** — files
- shipped and developed with **Docker**; production often on **Kubernetes**

So the Invenio question is also a Python + SQL + Docker + K8s question. That is why this folder sits last.

## Features that matter for nuclear data

| Invenio concept | Data Bank analogue |
|---|---|
| Record + DataCite-like metadata | JEFF library, code package, benchmark, report |
| Community | JEFF project, ICSBEP, IRPhEP, WPEC, computer program service |
| Files + checksums | ENDF tapes, ACE sets, handbooks, code tarballs |
| Versioning | JEFF-3.3 → JEFF-4.0, code revisions |
| Restricted access | member-only codes and some processed data |
| REST API | pipelines that publish a processed product without a web form |
| DOI | citable Data Bank outputs |

## Artefacts

- `sample_record.json` — a JEFF-like record shaped as Invenio/DataCite metadata
- `custom_fields.md` — nuclear-data fields I would propose rather than stuffing everything into the description
- `day-one-questions.md` — what I would ask the current platform owner

## Interview sentence

“I have not run Invenio in production. I have spent years creating the objects it would catalogue — evaluated files, processed ACE products, EXFOR comparisons and experimental benchmarks — and I have mapped those objects onto Invenio’s record/community/file/DOI model. That is the contribution I can make in month one while I learn the operator side of the platform.”
