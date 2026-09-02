#!/usr/bin/env bash
# Linux piece 3 — campaign runner
#
# Job mapping
#   Integrated pipelines on Linux. Check the environment, validate inputs,
#   then run the batch wrapper. One command is the production path.
set -euo pipefail

usage() {
  echo "usage: $0 -i INPUT_DIR -o OUTPUT_DIR -t TAG" >&2
  exit 2
}

INPUT_DIR=""
OUTPUT_DIR=""
TAG="untagged"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"

while getopts "i:o:t:h" opt; do
  case "$opt" in
    i) INPUT_DIR=$OPTARG ;;
    o) OUTPUT_DIR=$OPTARG ;;
    t) TAG=$OPTARG ;;
    *) usage ;;
  esac
done

[[ -n "$INPUT_DIR" && -n "$OUTPUT_DIR" ]] || usage

bash "$ROOT/scripts/check_env.sh"
bash "$ROOT/scripts/validate_inputs.sh" -i "$INPUT_DIR"
bash "$ROOT/scripts/batch_process.sh" -i "$INPUT_DIR" -o "$OUTPUT_DIR" -t "$TAG"
echo "campaign=$TAG status=ok"
