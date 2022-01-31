#! /bin/bash -e

CFLAGS="-Os -save-temps=obj -fdata-sections -ffunction-sections"

if [ "$1" = "clean" ]; then
    rm -rf test* *.i *.s *.o *.map
    echo "Clean build done !"
    exit 0
elif [ "$1" = "ok" ]; then
    cmd="gcc $CFLAGS -c 1.ok.c -o 1.ok.o"
    echo $cmd && $cmd
    cmd="gcc $CFLAGS -c 2.c -o 2.o"
    echo $cmd && $cmd
    cmd="gcc $CFLAGS 1.ok.o 2.o -o test.ok"
    echo $cmd && $cmd
elif [ "$1" = "fail" ]; then
    cmd="gcc $CFLAGS -c 1.fail.c -o 1.fail.o"
    echo $cmd && $cmd
    cmd="gcc $CFLAGS -c 2.c -o 2.o"
    echo $cmd && $cmd
    cmd="gcc $CFLAGS 1.fail.o 2.o -o test.fail"
    echo $cmd && $cmd
else
	cmd="Error input."
	echo $cmd 
fi

exit 0