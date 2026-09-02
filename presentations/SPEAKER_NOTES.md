# Speaker notes — one card per tool

Use these if the panel asks you to “present each tool”. Keep each card to about 60–90 seconds.

## C++
I use C++ when a numeric kernel must have an explicit contract: sorted energy grid, declared interpolation, no silent extrapolation. On my CV that sits next to Fortran CFD / digital-twin work on Linux HPC. The Data Bank does not need another language war. It needs kernels that still give the same answer after the author has left.

## Python
Python is the orchestration layer. I have built ingestion frameworks that isolate performance metrics from auxiliary inputs and fail when syntax or identifiers are wrong. That is how I would wrap NJOY or FRENDY so a JEFF tape processed in 2026 can be reconstructed in 2032.

## Linux
Linux is not a skill I list for decoration. It is the machine where the codes run. Batch scripts, modules, logs with compiler and code versions, separate run and publish directories. If I cannot replay it from a shell, it is not a service.

## Git / GitHub / GitLab
JEFF official files already live on the NEA GitLab. I treat version control as the scientific record: evaluation, processing input, image digest, review. Exploratory research code and production tags can share an organisation if the branches are honest.

## Docker
I containerise tools so the environment is pinned. Licensed nuclear data does not go in the image. The image digest goes in the audit table next to the output checksum.

## Kubernetes
Familiarity, not a production war story. Stateless APIs as Deployments, burst processing as Jobs, probes and resource requests I can explain. I would adopt the Data Bank’s existing cluster conventions rather than invent Helm charts for sport.

## Azure
Same honesty. AKS, ACR, PostgreSQL, Blob, Key Vault, Monitor is the map I would start from. First question on day one: what is the landing zone already?

## Java
JANIS is a Java Data Bank product I have used to compare JEFF, ENDF and EXFOR. Legacy migration starts by freezing that behaviour in tests. I have done the same pattern with legacy engineering procedures: re-implement structure, keep the decisions.

## SQL / NoSQL
Identifiers, versions, permissions and audit belong in SQL. Large files belong in object storage. Irregular experimental records can be documents. Search is a separate index. That is also how Invenio is built.

## Invenio RDM
Advantage item. NEA already runs an Invenio-based platform and mints DataCite DOIs. I map JEFF products, ACE sets, codes and benchmarks onto records, communities, files and restricted access. I will learn the operator side on the public compose install; I will not claim I have administered yours.
