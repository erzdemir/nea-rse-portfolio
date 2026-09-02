#!/usr/bin/env bash
# Linux Project — environment contract
# Job: Experience with Linux-based operating systems.
# A Data Bank run must record host, user, date and tool versions.
set -euo pipefail

echo "host=$(hostname)"
echo "user=$(id -un)"
echo "date=$(date -u +%Y-%m-%dT%H:%M:%SZ)"
echo "pwd=$(pwd)"
echo "bash=$BASH_VERSION"
command -v python3 >/dev/null && python3 --version || echo "python3=missing"
command -v g++ >/dev/null && g++ --version | head -n 1 || echo "g++=missing"
command -v cmake >/dev/null && cmake --version | head -n 1 || echo "cmake=missing"
