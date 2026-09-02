#!/usr/bin/env bash
# Linux piece 2 — validate a campaign input tree before processing.
#
# Job mapping
#   Business-logic consistency on Linux: do not start NJOY on an empty
#   or undeclared input set.
set -euo pipefail

usage() {
  echo "usage: $0 -i INPUT_DIR [-n EXPECTED_FILES]" >&2
  exit 2
}

INPUT_DIR=""
EXPECTED=""

while getopts "i:n:h" opt; do
  case "$opt" in
    i) INPUT_DIR=$OPTARG ;;
    n) EXPECTED=$OPTARG ;;
    *) usage ;;
  esac
done

[[ -n "$INPUT_DIR" ]] || usage
[[ -d "$INPUT_DIR" ]] || { echo "missing input dir: $INPUT_DIR" >&2; exit 1; }

if [[ -f "$INPUT_DIR/job.env" ]]; then
  # shellcheck disable=SC1091
  source "$INPUT_DIR/job.env"
fi

n_files=$(find "$INPUT_DIR" -type f ! -name 'job.env' | wc -l | tr -d ' ')
echo "input_dir=$INPUT_DIR"
echo "n_files=$n_files"

need=${EXPECTED:-${EXPECTED_FILES:-}}
if [[ -n "${need}" ]]; then
  if [[ "$n_files" -lt "$need" ]]; then
    echo "error: expected at least $need data files, found $n_files" >&2
    exit 1
  fi
  echo "expected_files=$need status=ok"
else
  if [[ "$n_files" -lt 1 ]]; then
    echo "error: input tree has no data files" >&2
    exit 1
  fi
  echo "status=ok"
fi
