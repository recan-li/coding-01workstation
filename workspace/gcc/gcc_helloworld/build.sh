#! /bin/bash -e

if [ "$1" = "clean" ]; then
    rm -rf test* *.i *.s *.o *.map
    echo "Clean build done !"
    exit 0
elif [ "$1" = "step" ]; then
	if [ "$2" = "cross" ]; then
		cross="arm-none-eabi-"
	fi
    cmd=$cross"gcc -E main.c -o main.i"
    echo $cmd && $cmd
    cmd=$cross"gcc -E sub.c -o sub.i"
    echo $cmd && $cmd
    cmd=$cross"gcc -S main.i -o main.s"
    echo $cmd && $cmd
    cmd=$cross"gcc -S sub.i -o sub.s"
    echo $cmd && $cmd
    cmd=$cross"gcc -c main.s -o main.o"
    echo $cmd && $cmd
    cmd=$cross"gcc -c sub.s -o sub.o"
    echo $cmd && $cmd
    cmd=$cross"gcc main.o sub.o -o test"
    echo $cmd && $cmd
elif [ "$1" = "allinone" ]; then
	cmd="gcc -c main.c -o main.o -save-temps=obj"
	echo $cmd && $cmd
	cmd="gcc -c sub.c -o sub.o -save-temps=obj"
	echo $cmd && $cmd
	cmd="gcc main.o sub.o -o test"
	echo $cmd && $cmd
else
	cmd="gcc main.c sub.c -o test"
	echo $cmd && $cmd
fi

exit 0