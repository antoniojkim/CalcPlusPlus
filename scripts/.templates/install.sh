#!/usr/bin/env bash
set -euo pipefail

wget https://github.com/antoniojkim/CalcPlusPlus/releases/latest/download/calcplusplus.tar.gz

SHA256="{SHA256SUM}"
if echo "$SHA256 calcplusplus.tar.gz | sha256sum --check --status"; then
    tar -xzvf calcplusplus.tar.gz
fi
