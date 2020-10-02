#!/usr/bin/env bash
set -euo pipefail

wget https://github.com/antoniojkim/CalcPlusPlus/releases/latest/download/calcplusplus.tar.gz

SHA256="272574fe3ab18c3b8ea6dbfbee8ee4f6f1649312fb7e3f3f847eb644d097a659"
if echo "$SHA256 calcplusplus.tar.gz | sha256sum --check --status"; then
    tar -xzvf calcplusplus.tar.gz
fi
