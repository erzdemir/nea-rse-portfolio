# NEA Data Bank — Research Software Engineer Portfolio

**Erdal Özdemir, Ph.D.**  
Computational Nuclear Researcher · Antalya, Türkiye  
`eozdemireoz@gmail.com`

Interview preparation repository for the **OECD Nuclear Energy Agency — Research Software Engineer** (Data Bank, Paris, Grade CF5).

This repository is not a claim that every listed technology was used in production at the same depth. It is a structured mapping of:

1. What the vacancy asks for
2. What I have already delivered in nuclear science / engineering software
3. Concrete, reviewable artefacts I can walk through in an interview
4. A short, honest plan for the advantage items I have not yet used in production (Azure, Kubernetes, InvenioRDM)

---

## Why this role fits

The Data Bank is the international reference centre for **computer codes and nuclear data**. The vacancy is not a generic DevOps post. It asks for someone who can:

- write **exploratory research code** *and* **long-lived production software**
- sit between **scientists, engineers and informaticians**
- keep **business logic consistent** while migrating **legacy Java** services
- build frameworks for **nuclear physics data, experimental benchmarks** and related datasets
- operate in **Linux + Git + containers**, with Azure / Kubernetes familiarity
- present work to **NEA committees, expert groups and conferences**

That is the shape of my last decade: Ph.D. Nuclear Engineering (University of Tokyo), JEFF/ENDF/EXFOR processing with NJOY and FRENDY, ACE generation for MCNP, JANIS-based comparison, C++/Fortran CFD and digital-twin work on Linux HPC, Python ingestion pipelines with explicit business-logic guards, Git-based research-to-production repositories, and presentations at NURETH and specialists’ meetings. I am also an alumnus of the **OECD NEA International School on Simulation of Nuclear Reactor Systems**.

---

## Vacancy tools → this repository

| Vacancy item | Strength | Artefact |
|---|---|---|
| C++ / Fortran / Python (scientific computing) | Strong, production + research | [`01-cpp-scientific`](01-cpp-scientific), [`02-python-pipelines`](02-python-pipelines) |
| Linux-based operating systems | Strong (HPC + daily Unix) | [`03-linux-hpc`](03-linux-hpc) |
| Git / GitHub / GitLab | Strong | this repository + Data Bank GitLab awareness |
| Docker / containerisation | Practical (Docker); K8s learning path | [`04-containers-azure`](04-containers-azure) |
| Azure cloud | Familiarity required — **learning path + architecture notes**, not fake production claims | [`04-containers-azure`](04-containers-azure) |
| Java (advantage) | Listed skill + JANIS user; migration pattern demo | [`05-java-legacy-migration`](05-java-legacy-migration) |
| SQL / NoSQL (advantage) | SQL + pipeline / datastore design | [`06-sql-nosql`](06-sql-nosql) |
| Invenio RDM (advantage) | Domain mapping, not production admin | [`07-invenio-rdm`](07-invenio-rdm) |

Supporting material:

- [`docs/STAR_STORIES.md`](docs/STAR_STORIES.md) — interview stories in STAR form, written in the language of the vacancy
- [`docs/INTERVIEW_QA.md`](docs/INTERVIEW_QA.md) — likely technical and competency questions
- [`docs/STUDY_PLAN.md`](docs/STUDY_PLAN.md) — 21-day plan for Azure, Kubernetes and InvenioRDM
- [`presentations/`](presentations/) — slide deck for the Tools & Technical Skills part of the interview

---

## How to use this in the interview

Do **not** walk through every folder. Pick two deep examples and one honest gap:

1. **Deep match:** ENDF/JEFF processing pipeline + business-logic isolation (Python + Linux + Git + nuclear data formats the Data Bank actually ships).
2. **Deep match:** C++/Fortran scientific kernels on HPC, packaged so a colleague can reproduce a run.
3. **Honest gap + plan:** “I have not administered InvenioRDM or an Azure AKS cluster in production. Here is how the Data Bank’s nuclear-data objects map onto Invenio records, and here is a Docker Compose / Helm-shaped deployment I would start from.”

That combination reads as a scientist-engineer who already speaks Data Bank language, not as a generalist padding a CV.

---

## Domain systems I can discuss without notes

- Evaluated libraries: **JEFF, ENDF**, comparison with **EXFOR**
- Processing: **NJOY, FRENDY**, ACE generation for **MCNP**
- Visualisation / comparison: **JANIS** (Java-based Nuclear Information System — a Data Bank product)
- Benchmarks and experimental datasets, including aerosol-deposition style collections
- NEA GitLab as the current home of JEFF official releases and code/data pipelines
- GRE@T-PIONEER modules: nuclear data, neutron transport, reactor transients / UQ

---

## Language note

OECD official languages are English and French. English is professional/fluent. French is a committed learning item, not a current working language. Say this once, clearly, and state the plan.

---

## Disclaimer on artefacts

Code in this repository is **illustrative interview material**. It uses public nuclear-data *concepts* and tiny synthetic snippets. It does not redistribute restricted Data Bank packages, licensed ACE libraries, or employer-proprietary source.
