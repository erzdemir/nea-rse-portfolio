# Likely questions and disciplined answers

OECD selection may include a video interview, a job-based assessment and a panel. Prepare short answers. Do not lecture.

## Technical

**Which language would you pick for a new Data Bank service?**
Python for orchestration, APIs and Invenio-side work. C++/Fortran for numeric kernels that already exist or must be fast and stable. Java when the living system is already Java (JANIS and related tools) and the cost of a rewrite exceeds the benefit. The language is a consequence of the artefact’s life expectancy.

**How do you migrate a Java service?**
Characterise current behaviour with golden tests. Identify hidden defaults. Put a façade in front. Replace one capability at a time. Keep the old engine as oracle until numbers match within an agreed tolerance. Never start with a full rewrite.

**What does “business logic consistency” mean for nuclear data?**
Same MAT/MF/MT, same temperature, same interpolation law, same processor version → same numbers. Missing sections fail; they are not silently zeroed.

**How would you containerise NJOY or FRENDY?**
Pin the compiler and code version in the image. Mount input tapes read-only. Write outputs to a versioned volume. Record the image digest in the audit table. Do not bake licensed data into the image.

**SQL or NoSQL?**
SQL for identity, versions, permissions, audit. Object storage for bytes. Search index for discovery. Documents for irregular experimental records. Invenio already implements this split.

**What is InvenioRDM?**
A turn-key research data repository (Zenodo’s family): Python, PostgreSQL, OpenSearch, files, DOI minting, communities, REST API, Docker/K8s. NEA is already using an Invenio-based platform and DataCite DOIs. I would extend that model for JEFF products, codes and benchmarks.

**Azure vs on-prem?**
I would first ask what the Data Bank landing zone already is. Familiarity means I can place a service on AKS + ACR + PostgreSQL + Blob + Key Vault without designing a parallel universe.

**GitLab at NEA?**
JEFF official files and many Data Bank assets are already versioned on the NEA GitLab, with pipelines on the local datacentre. I would treat GitLab as the development source of truth and Invenio as the citable, permissioned publication layer.

## Domain

**What is the difference between ENDF, JEFF and EXFOR?**
ENDF is a format and also a US evaluation series. JEFF is the joint evaluated library coordinated through the NEA. EXFOR is compiled experimental data. Processing turns evaluations into application files; JANIS is how many users look at both.

**What is ACE?**
A continuous-energy application format used by MCNP (and others). Produced from evaluated files by NJOY or FRENDY. Temperature and reconstruction tolerances are part of the product.

**What Data Bank codes / tools can you name?**
JANIS, DICE (ICSBEP), IDAT (IRPhEP), SFCOMPO, NDaST, MeshTal Viewer, computer program service, JEFF project, NJOY/FRENDY processing.

## Competencies (OECD framework)

They assess Vision & Strategy (L1), Enable People (L1), Ethics & Integrity (L2), Collaboration (L2), Achieve Results (L2), Innovate & Embrace Change (L2).

- **Ethics:** nuclear data and member-only codes are not portfolio props. I do not put restricted tapes on a public GitHub.
- **Collaboration:** I have been the translator between physicists and computing practice.
- **Change:** migrate by tests, not by slogans.
- **Results:** a service that still runs after I leave.

## Gaps — scripted honesty

**French?**
English is my working international language. French is not yet at OECD working level. I will start structured learning immediately; I do not pretend otherwise.

**Kubernetes / Azure production?**
Docker and Linux are real. AKS operations are a familiarity target. I have architecture notes and a 21-day practice plan, not a fake production story.

**Invenio production?**
Domain mapping is real. Operator experience will be acquired on the job and on the public InvenioRDM docs / demo before joining.

## Questions I would ask them

1. Which Java services are in the first migration wave?
2. What is the intended relationship between GitLab, the computer program service and Invenio?
3. How are member-country access rules enforced today?
4. What does “production quality” mean for a code that is distributed once a year versus an API that is hit daily?
5. How does the Data Bank want exploratory physics codes and long-lived services governed in the same Git organisation?
6. What is the expected balance between maintaining JANIS and building the next platform?
