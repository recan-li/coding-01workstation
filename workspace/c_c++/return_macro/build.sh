#! /bin/bash -e

CFLAGS="-Wall -Werror -save-temps=obj"
cmd="gcc *.c $CFLAGS -o test"

if [ "$1" = "clean" ]; then
    rm -rf test
    echo "Clean build done !"
    exit 0
fi

echo $cmd && $cmd