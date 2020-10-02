#!/bin/bash

currdir=$(dirname $0)
tmp="${currdir#?}"

if [ "${currdir%$tmp}" != "/" ]; then
    currdir=$PWD/$dirname
fi

export LD_LIBRARY_PATH=$currdir/libs

$currdir/bin/calcpp "$@"
