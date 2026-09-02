#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$ROOT/data/output_demo"
rm -rf "$OUT"
bash "$ROOT/scripts/check_env.sh"
bash "$ROOT/scripts/batch_process.sh" -i "$ROOT/data/input" -o "$OUT" -t demo
test -f "$OUT/run_demo.log"
grep -q "status=ok" "$OUT/run_demo.log"
echo "linux demo ok"
