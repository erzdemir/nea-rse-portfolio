# 05 — Java and legacy-code migration

**Vacancy lines:**
- *Experience with Java would be an advantage*
- re-implementation of functionality from **legacy Java codebases** to other languages while **ensuring consistency of business logic and system behaviour**

This is one of the strongest alignments in the whole vacancy.

## Why this is not a generic “I know Java” slide

The Data Bank’s flagship nuclear-data viewer is **JANIS — Java-based Nuclear Information System**. It reads ENDF / PENDF / GENDF and EXFOR, compares evaluations, and has been a production service for more than two decades. Any serious conversation about “legacy Java at the Data Bank” that does not mention JANIS, DICE, IDAT or related Java tools is a conversation about the wrong organisation.

I am a **user and consumer** of JANIS in evaluation / comparison work (JEFF, ENDF, EXFOR). I also list Java among my languages and have evaluated legacy engineering procedure databases for re-implementation while keeping business logic intact.

I will not claim I am a JANIS core committer. I *will* claim I understand why you do not “just rewrite it in Python over a weekend”.

## Migration doctrine I would bring

1. **Inventory behaviour, not files.** What answers does the current system give for a known tape? Those answers are the specification.
2. **Characterise hidden contracts.** Interpolation defaults, temperature handling, missing-section behaviour, comparison tolerances.
3. **Build a characterisation test suite** before changing language.
4. **Strangle, don’t big-bang.** New API in front, old engine behind, one endpoint at a time.
5. **Keep an oracle.** For nuclear data, the old JANIS plot / number *is* often the acceptance test.

This is exactly the “consistency of business logic and system behaviour” sentence in the vacancy.

## Artefacts

- `src/main/java/nea/demo/CrossSectionRecord.java` — a tiny Java domain object in a style close to older scientific services (explicit fields, defensive checks).
- `python_port/xs_record.py` — the same contract in Python.
- `tests/golden.json` — the shared expected output. The test is the migration.

## Interview sentence

“I have used the Data Bank’s own Java tooling to inspect JEFF and ENDF files. If the assignment is to modernise parts of that estate, I would start by freezing the numerical behaviour in tests, then move services behind APIs, not by translating syntax line by line.”
