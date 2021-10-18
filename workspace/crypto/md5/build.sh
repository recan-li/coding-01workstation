#! /bin/bash -e

cmd="gcc *.c ../../utils/convert.c -I../../utils -o test"

if [ "$1" = "clean" ]; then
    rm -rf test
    echo "Clean build done !"
    exit 0
fi

echo $cmd && $cmd