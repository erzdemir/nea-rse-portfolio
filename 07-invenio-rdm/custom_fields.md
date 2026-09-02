# Custom fields I would propose

InvenioRDM supports custom fields so a nuclear data bank does not abuse the free-text description.

Minimum set:

- `nea:library` — JEFF-4.0, ENDF/B-VIII.1, …
- `nea:format` — ENDF-6, PENDF, GENDF, ACE, EXFOR
- `nea:processor` — NJOY version, FRENDY version, image digest
- `nea:temperature_K`
- `nea:mf` / `nea:mt` (or a controlled list of reaction identifiers)
- `nea:access_class` — public / member / restricted-code
- `nea:validation_status` — raw / processed / benchmarked
- `nea:related_code` — MCNP, SERPENT, PHITS, …

Communities rather than tags for living collaborations (JEFF, WPEC, ICSBEP).
