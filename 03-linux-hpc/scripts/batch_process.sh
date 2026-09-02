#!/usr/bin/env bash
# Linux Project — repeatable processing wrapper
#
# Job mapping
#   Linux/HPC operations; integrated pipelines; production software.
#   NJOY/FRENDY would be invoked here. This script only demonstrates
#   the operational contract around that call.
#
# Rules
#   - fail on first error
#   - require input and output directories
#   - write versions into the log
#   - keep the run directory separate from published artefacts
set -euo pipefail

usage() {
  echo "usage: $0 -i INPUT_DIR -o OUTPUT_DIR -t TAG" >&2
  exit 2
}

INPUT_DIR=""
OUTPUT_DIR=""
TAG="untagged"

while getopts "i:o:t:h" opt; do
  case "$opt" in
    i) INPUT_DIR=$OPTARG ;;
    o) OUTPUT_DIR=$OPTARG ;;
    t) TAG=$OPTARG ;;
    *) usage ;;
  esac
done

[[ -n "$INPUT_DIR" && -n "$OUTPUT_DIR" ]] || usage
[[ -d "$INPUT_DIR" ]] || { echo "missing input dir: $INPUT_DIR" >&2; exit 1; }

mkdir -p "$OUTPUT_DIR"
LOG="$OUTPUT_DIR/run_${TAG}.log"
PUBLISH="$OUTPUT_DIR/published"
mkdir -p "$PUBLISH"

{
  echo "tag=$TAG"
  echo "host=$(hostname)"
  echo "user=$(id -un)"
  echo "date=$(date -u +%Y-%m-%dT%H:%M:%SZ)"
  echo "input_dir=$INPUT_DIR"
  echo "output_dir=$OUTPUT_DIR"
  echo "n_files=$(find "$INPUT_DIR" -type f | wc -l)"
} | tee "$LOG"

# Placeholder for NJOY/FRENDY. Stage inputs and record each name.
find "$INPUT_DIR" -type f -print0 | while IFS= read -r -d '' f; do
  base=$(basename "$f")
  cp "$f" "$PUBLISH/${base}.staged"
  echo "staged $base" | tee -a "$LOG"
done

echo "status=ok" | tee -a "$LOG"
echo "log=$LOG"
