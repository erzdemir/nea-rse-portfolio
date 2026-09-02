# Linux operations — interview project

Vacancy: experience with Linux-based operating systems.

| Script | Role |
|---|---|
| scripts/check_env.sh | Record host, user, date, tool versions |
| scripts/validate_inputs.sh | Refuse an empty or short input tree |
| scripts/batch_process.sh | Stage files and write a run log |
| scripts/run_campaign.sh | Production path: env -> validate -> batch |

Run:
  bash tests/run_demo.sh
  bash scripts/run_campaign.sh -i data/input -o data/output -t demo

NJOY/FRENDY would replace the copy step inside batch_process.sh.
Do not commit data/output or data/output_demo.
