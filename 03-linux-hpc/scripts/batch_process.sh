#!/usr/bin/env bash
# Illustrative HPC-style wrapper. Interview artefact only.
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

{
  echo "tag=$TAG"
  echo "host=$(hostname)"
  echo "date=$(date -u +%Y-%m-%dT%H:%M:%SZ)"
  echo "user=$(id -un)"
  echo "pwd=$(pwd)"
  command -v python3 >/dev/null && python3 --version
  echo "input_dir=$INPUT_DIR"
  echo "n_files=$(find "$INPUT_DIR" -type f | wc -l)"
} | tee "$LOG"

# Placeholder for a real NJOY/FRENDY invocation.
# A production wrapper would pin binary versions and checksum inputs here.
find "$INPUT_DIR" -type f -name '*.txt' -print0 \
  | while IFS= read -r -d '' f; do
      base=$(basename "$f")
      cp "$f" "$OUTPUT_DIR/${base}.staged"
      echo "staged $base" | tee -a "$LOG"
    done

echo "status=ok" | tee -a "$LOG"
