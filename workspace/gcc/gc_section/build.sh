#! /bin/bash -e

CFLAGS="-save-temps=obj -Wall"
LDFLAGS="-Wl,-Map=test.map"

CFLAGS_GC="-fdata-sections -ffunction-sections"
LDFLAGS_GC="-Wl,--gc-sections"
LDFLAGS_MAP_GC="-Wl,-Map=test_gc.map"

PRINT_GC="-Wl,--print-gc-sections"

GCC_LDS=default.lds

if [ "$1" = "clean" ]; then
    rm -rf test* *.i *.s *.o *.map
    echo "Clean build done !"
    exit 0
elif [ "$1" = "gc" ]; then
	echo "gcc compile with gc ..."
	single_c_file=`ls *.c | cut -d . -f 1`
	cmd1="gcc -o $single_c_file.o -c *.c $CFLAGS $CFLAGS_GC"
	cmd2="gcc -o test_gc $single_c_file.o $LDFLAGS_GC $LDFLAGS_MAP_GC -T $GCC_LDS $PRINT_GC"
	echo "$cmd1 && $cmd2" && $cmd1 && $cmd2
else
	echo "gcc compile without gc ... (default)"
	cmd="gcc *.c $CFLAGS $LDFLAGS -o test"
	echo $cmd && $cmd
fi

exit 0