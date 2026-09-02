# 03 — Linux / Unix and HPC environments

**Vacancy line:** *Experience with Linux-based Operating Systems*

## What I would say in the interview

Linux is the environment in which nuclear codes, processing chains and Data Bank services actually live. My daily work has been Unix/Linux and HPC: batch submission, module environments, filesystem conventions for large tapes, and shell automation that other people can rerun.

I treat the shell as part of the scientific record. A processing campaign that cannot be replayed from a script is not a Data Bank service; it is a notebook.

## Experience this folder represents

- Linux HPC for C++ / Fortran CFD and digital-twin frameworks
- NJOY / FRENDY / MCNP-style processing chains
- Git + bash as the glue between research experiments and repeatable runs
- Docker later sits *on top* of this, it does not replace it

## Artefact

`scripts/batch_process.sh` shows the operational habits I would bring:

- `set -euo pipefail`
- explicit working directory and log file
- version pins written into the log (compiler, code, library tag)
- non-zero exit if a required input is absent
- separation of “run directory” and “published artefact directory”

## Talking points for the Data Bank

- JEFF processing and code validation already run on NEA infrastructure / GitLab pipelines.
- A Research Software Engineer must be comfortable on a headless Linux box at 07:00 when a pipeline failed on an ENDF tape, not only in a cloud console.
- Container images should be built *from* a known Linux userspace, not used to hide an unreproducible laptop setup.
