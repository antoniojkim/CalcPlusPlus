#!/usr/bin/env bash
set -euo pipefail

wget https://github.com/antoniojkim/CalcPlusPlus/releases/latest/download/calcplusplus.tar.gz

SHA256="2d3318b63b5a606fb1ecb64dd1e7570561051d1e0f81da20459cb218f06c0207"
if echo "$SHA256 calcplusplus.tar.gz | sha256sum --check --status"; then
    tar -xzvf calcplusplus.tar.gz
fi
