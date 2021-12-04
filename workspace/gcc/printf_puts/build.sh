#! /bin/bash -e

CFLAGS="-Wall -Werror -save-temps=obj"
cmd="gcc *.c $CFLAGS -o test"

if [ "$1" = "clean" ]; then
    rm -rf test
    echo "Clean build done !"
    exit 0
fi

if [ "$1" = "cross" ]; then
    cmd="arm-none-eabi-"$cmd
fi

echo $cmd && $cmd