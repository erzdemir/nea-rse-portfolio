# Linux project — spoken notes (about 90 seconds)

Vacancy: Linux-based operating systems; production software; pipelines.

Open batch_process.sh and point at:
  set -euo pipefail
  required -i and -o
  log contains host, user, date, tag
  published artefacts sit in a separate directory

Say:
  A processing campaign that cannot be replayed from a script
  is not a Data Bank service. NJOY or FRENDY would replace the
  copy step. The wrapper stays the same.

Live demo:
  bash scripts/check_env.sh
  bash scripts/batch_process.sh -i data/input -o data/output -t demo
  cat data/output/run_demo.log
