# 04 — Docker, Kubernetes and Azure

**Vacancy lines:**
- *Familiarity with Azure cloud environments and containerisation (Docker/Kubernetes)*
- maintain Data Bank digital services, interfaces and associated infrastructure

## Honest position (say this first)

- **Docker:** I have used it to package scientific tools and to keep research and production environments from drifting.
- **Kubernetes / Azure:** the vacancy asks for *familiarity*, not “principal cloud architect”. I have not run a production AKS cluster for the Data Bank. I *do* understand why the Data Bank would put long-lived services (JANIS backends, catalogue APIs, Invenio, GitLab runners) on containers and a managed cloud, and I can discuss the design.

Never invent Azure production stories. Interviewers in international organisations test this immediately.

## How I would talk about it

A Data Bank service has different constraints from a startup web app:

| Concern | Why it matters here |
|---|---|
| Bit-level reproducibility | Processed ACE / PENDF products must be rebuildable years later |
| Access control | Member-country codes and some data are not public |
| Long support window | 36-month post, but services outlive contracts |
| Mixed runtimes | Fortran kernels, Java UIs, Python APIs, databases |
| Audit | Which image digest processed JEFF-4.0 file X? |

Containers help because the image *is* the environment. Kubernetes / Azure help because the Data Bank should not be one irreplaceable Linux workstation.

## Artefacts

- `Dockerfile` — multi-stage style image for the Python ingest tool
- `docker-compose.yml` — API + PostgreSQL local stack (mirrors how Invenio is often first installed)
- `k8s/deployment.yaml` — a reading-level Deployment + Service (what I would start from on AKS)
- `azure/architecture-notes.md` — Azure services I would evaluate, with reasons, not a shopping list

## 30-second Azure map I would use

- **AKS** for stateless APIs and workers
- **Azure Container Registry** for signed, version-pinned images
- **Azure Database for PostgreSQL** for Invenio / catalogue metadata
- **Blob Storage** for large ENDF/ACE/benchmark files (immutability policy)
- **Key Vault** for member-access secrets
- **Monitor + Log Analytics** for pipeline failure alerts
- **Entra ID** for staff SSO; separate pattern for member-country users

## Learning path

See [`../docs/STUDY_PLAN.md`](../docs/STUDY_PLAN.md). Before the interview I will be able to: build and push an image, describe an AKS node pool vs. a job, and explain Helm vs. raw manifests without pretending I have operated NEA production.
