#!/usr/bin/env bash
set -euo pipefail

mkdir -p ".package/CalcPlusPlus"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    python -u scripts/package.py
    cd .package/
    tar -czvf calcplusplus.tar.gz CalcPlusPlus/
    sha256sum calcplusplus.tar.gz
elif [[ "$OSTYPE" == "darwin"* ]]; then
    cp -r UI/calcpp.app .package/CalcPlusPlus/calcpp.app
    cp MathEngine/libMathEngine.dylib .package/CalcPlusPlus/calcpp.app/Contents/Resources/
    cd .package/
    tar -czvf calcplusplus.bottle.tgz CalcPlusPlus/
    sha256sum calcplusplus.bottle.tgz | cut -d " " -f 1 | pbcopy
else
    echo "Unsupported OS: $OSTYPE"
fi
