#!/bin/bash

dirname=$(dirname $0)
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
    dirname=$PWD/$dirname
fi

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    LD_LIBRARY_PATH=$dirname/libs
    export LD_LIBRARY_PATH
elif [[ "$OSTYPE" == "darwin"* ]]; then
    DYLD_LIBRARY_PATH=$dirname/libs
    export DYLD_LIBRARY_PATH
fi
QT_PLUGIN_PATH=$dirname
export QT_PLUGIN_PATH

$dirname/bin/calcpp "$@"
