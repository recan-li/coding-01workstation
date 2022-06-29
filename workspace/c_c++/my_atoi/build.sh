#! /bin/bash -e

CFLAGS="-Wall -save-temps=obj"
cmd="gcc *.c $CFLAGS -o test"

if [ "$1" = "clean" ]; then
    rm -rf test
    echo "Clean build done !"
    exit 0
elif [ "$1" = "macro" ]; then
	cmd+=" -DMACRO_DEFINE_EN=1"
	echo $cmd && $cmd
else
	echo $cmd && $cmd
fi

