
if [ "$1" == "clean" ]; then
	rm -rf test*
	exit 0
fi

if [ "$1" == "0" ]; then
	echo "old project"
	cp config_old.h config.h
elif [ "$1" == "1" ]; then
	echo "test project"
	cp config_test.h config.h
else
	echo "new project"
	cp config_new.h config.h
fi

rm -rf test
gcc -o test main.c -save-temps=obj
./test
