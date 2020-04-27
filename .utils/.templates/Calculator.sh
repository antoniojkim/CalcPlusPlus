#!/bin/bash

dirname=$(dirname $0)
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
    dirname=$PWD/$dirname
fi

LD_LIBRARY_PATH=$dirname/libs
export LD_LIBRARY_PATH
QT_PLUGIN_PATH=$dirname
export QT_PLUGIN_PATH

$dirname/bin/CalcUI "$@"