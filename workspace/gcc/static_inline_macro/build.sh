#! /bin/bash

CFLAGS="-save-temps=obj -Wall"
LDFLAGS_NOSTATIC="-Wl,-Map=test_nostatic.map"
LDFLAGS_STATIC="-Wl,-Map=test_static.map"

if [ "$1" = "clean" ]; then
    rm -rf test* *.i *.s *.o
    echo "Clean build done !"
    exit 0
elif [ "$1" = "error" ]; then
    echo "------------------------------------"
	echo "gcc compile with static ... (FAIL)"
	cmd="gcc main.c $CFLAGS -DERROR_CASE -o test_static $LDFLAGS_STATIC"
	echo $cmd && $cmd
	echo "------------------------------------"
else
	echo "------------------------------------"
	echo "gcc compile with static ... (OK)"
	cmd="gcc main.c $CFLAGS -o test_static $LDFLAGS_STATIC"
	echo $cmd && $cmd
	echo "------------------------------------"
fi

exit 0