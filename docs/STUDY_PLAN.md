# 21-day study plan for the advantage / familiarity items

Use this if the interview is not tomorrow. If it is tomorrow, do **Days 1–3 only** and rely on honest framing.

## Days 1–3 — vocabulary you must not mix up

- Read InvenioRDM docs: install overview, records, communities, REST API, files.
- Click through the public demo and Zenodo (same family).
- Read one DataCite-at-NEA slide deck / talk notes: DOIs on publications and JEFF-class products.
- Sketch on paper: GitLab (develop) → pipeline (process) → Invenio (publish/cite).
- Revise JANIS capabilities so you can speak as a power user.

Deliverable: a one-page diagram in your notebook.

## Days 4–8 — Docker until it is boring

- Build the image in `04-containers-azure`.
- Add a second service (postgres) with compose.
- Break it on purpose (wrong tag, missing volume) and read the logs.
- Multi-stage build: compile a tiny C++ binary, copy only the runtime.

Deliverable: you can explain layers, digests, and why data does not belong in the image.

## Days 9–14 — Kubernetes locally

- `kind` or `minikube`.
- Apply the sample Deployment/Service.
- `kubectl logs`, `describe`, rollout undo.
- Convert the manifest to a two-value Helm chart (image tag, replica count).
- Read, do not memorise: probes, requests/limits, ConfigMap vs Secret.

Deliverable: you can talk through a failed rollout.

## Days 15–18 — Azure familiarity

Microsoft Learn paths (free):

- Azure Kubernetes Service core concepts
- Azure Container Registry
- Azure Database for PostgreSQL
- Blob storage tiers + immutability
- Key Vault + managed identity

If you can afford it, a tiny personal subscription: push one image to ACR, run one Container App or a one-node AKS, delete it.

Deliverable: the architecture notes in this repo, spoken out loud in three minutes.

## Days 19–21 — Invenio hands-on

- Follow the official InvenioRDM local install (docker-compose).
- Create one community and one restricted record.
- Hit the REST API with a token.
- Add a custom field conceptually (even if you only write the JSON).

Deliverable: five-minute live demo on your laptop if they ask.

## Daily 20 minutes — French

OECD expects English plus a commitment to French.

- Working phrases: committees, data bank, nuclear data, software, pipeline, legacy, benchmark.
- Do not attempt the interview in French unless you can.
- Have a concrete course name and schedule ready if they ask.

## What not to do

- Do not put “Azure / Kubernetes / Invenio expert” on a revised CV after six evenings.
- Do not upload copyrighted nuclear data to a public repository.
- Do not cram OECD competency jargon. Use one real example each.
