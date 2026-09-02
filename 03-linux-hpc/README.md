# Linux operations — interview project

Vacancy: experience with Linux-based operating systems.

This folder is the operational wrapper around nuclear-data processing.
It does not contain NJOY. It shows how a repeatable Linux campaign is run.

Scripts:
  scripts/check_env.sh       record host, user, date, tool versions
  scripts/batch_process.sh   require input/output, write a log, publish staged files
  tests/run_demo.sh          smoke test

Run (Git Bash or Linux):
  bash scripts/check_env.sh
  bash scripts/batch_process.sh -i data/input -o data/output -t demo
  bash tests/run_demo.sh

Do not commit data/output or data/output_demo.
