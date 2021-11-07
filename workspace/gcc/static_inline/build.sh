#! /bin/bash

CFLAGS="-save-temps=obj -Wall"
LDFLAGS_NOSTATIC="-Wl,-Map=test_nostatic.map"
LDFLAGS_STATIC="-Wl,-Map=test_static.map"

if [ "$1" = "clean" ]; then
    rm -rf test* *.i *.s *.o
    echo "Clean build done !"
    exit 0
else
	echo "------------------------------------"
	echo "gcc compile without static ..."
	cmd="gcc main_nostatic.c $CFLAGS -o test_nostatic $LDFLAGS_NOSTATIC"
	echo $cmd && $cmd
	echo "------------------------------------"
	echo "gcc compile with static ..."
	cmd="gcc main.c $CFLAGS -o test_static $LDFLAGS_STATIC"
	echo $cmd && $cmd
	echo "------------------------------------"
fi

exit 0