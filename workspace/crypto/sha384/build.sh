#! /bin/bash -e

# SHA384 depend on sha512.c
CFLAGS="-Wall -Werror"
cmd="gcc *.c ../sha512/sha512.c -I../sha512 ../../utils/convert.c -I../../utils $CFLAGS -o test"

if [ "$1" = "clean" ]; then
    rm -rf test
    echo "Clean build done !"
    exit 0
fi

echo $cmd && $cmd