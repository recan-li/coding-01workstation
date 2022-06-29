#! /bin/bash -e

if [ "a" == "b" ]; then
    CROSSgcc=arm-none-eabi-gcc
    CROSSar=arm-none-eabi-ar
    SPECS="--specs=nosys.specs"
else
    CROSSgcc=gcc
    CROSSar=ar
    SPECS=
fi

if [ "$1" = "clean" ]; then
    rm -rf test* *.i *.s *.o *.map *.a
    echo "Clean build done !"
    exit 0
else
	cmd="$CROSSgcc -c main.c -o main.o -save-temps=obj"
	echo $cmd && $cmd
	cmd="$CROSSgcc -c a.c -o a.o -save-temps=obj"
	echo $cmd && $cmd
    cmd="$CROSSgcc -c b.c -o b.o -save-temps=obj"
    echo $cmd && $cmd
    cmd="$CROSSgcc -c c.c -o c.o -save-temps=obj"
    echo $cmd && $cmd
    cmd="$CROSSgcc -c libd.c -o libd.o -save-temps=obj"
    echo $cmd && $cmd
    cmd="$CROSSar -rcs libd.a libd.o"
    echo $cmd && $cmd
    cmd="$CROSSgcc -c libe.c -o libe.o -save-temps=obj"
    echo $cmd && $cmd
    cmd="$CROSSar -rcs libe.a libe.o"
    echo $cmd && $cmd
    cmd="$CROSSgcc -c libf.c -o libf.o -save-temps=obj"
    echo $cmd && $cmd
    cmd="$CROSSar -rcs libf.a libf.o"
    echo $cmd && $cmd
    if [ "$1" = "ok" ]; then
        # c.o before -ld
        cmd="$CROSSgcc a.o b.o main.o c.o -ld -L./ -lc $SPECS -o test"
        echo $cmd && $cmd
    elif [ "$1" = "fail" ]; then
        # c.o after -ld
        cmd="$CROSSgcc a.o b.o main.o -ld -L./ c.o -lc $SPECS -o test"
        echo $cmd && $cmd
    elif [ "$1" = "fail-solve" ]; then
        # c.o after -ld
        cmd="$CROSSgcc -Wl,--whole-archive -Wl,--start-group a.o b.o mai.o -ld -L./ c.o -lc -Wl,--end-group -Wl,-no-whole-archive $SPECS -o test"
        echo $cmd && $cmd
    elif [ "$1" = "mul-lib-ok" ]; then
        # re-compile libd.c
        cmd="$CROSSgcc -c libd.c -o libd.o -save-temps=obj -DMUL_LIB_TEST"
        echo $cmd && $cmd
        cmd="$CROSSar -rcs libd.a libd.o"
        echo $cmd && $cmd
        # link in order ? link ok
        cmd="$CROSSgcc a.o b.o c.o main.o -ld -le -lf -L./ -lc $SPECS -o test"
        echo $cmd && $cmd
    elif [ "$1" = "mul-lib-fail" ]; then
        # re-compile libd.c
        cmd="$CROSSgcc -c libd.c -o libd.o -save-temps=obj -DMUL_LIB_TEST"
        echo $cmd && $cmd
        cmd="$CROSSar -rcs libd.a libd.o"
        echo $cmd && $cmd
        # link in order ? link fail
        cmd="$CROSSgcc a.o b.o c.o main.o -lf -ld -le -L./ -lc $SPECS -o test"
        echo $cmd && $cmd
    elif [ "$1" = "mul-lib-fail-solve" ]; then
        # re-compile libd.c
        cmd="$CROSSgcc -c libd.c -o libd.o -save-temps=obj -DMUL_LIB_TEST"
        echo $cmd && $cmd
        cmd="$CROSSar -rcs libd.a libd.o"
        echo $cmd && $cmd
        # link together, link ok
        cmd="$CROSSgcc -Wl,--whole-archive -Wl,--start-group a.o b.o c.o main.o -lf -ld -le -L./ -lc -Wl,--end-group -Wl,-no-whole-archive $SPECS -o test"
        echo $cmd && $cmd
    fi
fi

exit 0