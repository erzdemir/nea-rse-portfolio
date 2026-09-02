# Azure notes for the Data Bank conversation

## What I would *not* say

“I migrated the Data Bank to Azure.” I did not.

## What I would say

OECD/NEA already operates digital services and GitLab-centred pipelines. A Research Software Engineer should be able to place a new service on the organisation’s existing landing zone rather than invent a parallel cloud.

## Candidate building blocks

1. **Identity.** Staff via Entra ID / OECD SSO. Member-country users may need a different federation pattern. Never store credentials in Git.
2. **Compute.** AKS for long-running APIs (catalogue, Invenio, internal tools). Azure Container Apps or Jobs for burst NJOY/FRENDY-style processing if the kernel is containerised.
3. **Data.** PostgreSQL for metadata. Blob Storage with immutability and lifecycle rules for large nuclear-data objects. Redis only as cache / broker, never as system of record.
4. **Registry.** ACR with image digest pinning. The digest goes into the audit record of every processed file.
5. **Secrets.** Key Vault. Rotation is part of operations, not an afterthought.
6. **Observability.** Pipeline failure on a JEFF tape must page a human with the tape name, image digest and exit code.
7. **Network.** Private endpoints for databases. Public exposure only for services that are meant to be public (JANIS web, public library pages).

## Questions I would ask on day 1

- Is Azure already the Data Bank landing zone, or is there an on-prem datacentre plus selected cloud services?
- Who owns GitLab runners today?
- What is the current backup / restore drill for the catalogue database?
- Which services are still single-VM Java processes?
