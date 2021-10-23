#!/bin/bash -e

crypto_list=(`ls -l | grep '^d' | awk '{ print $9 }'`)

function build_and_test_crypto()
{
	crypto=$1
	cd $crypto
	echo "build $crypto ..."
	./build.sh clean && ./build.sh
	echo "test $crypto ..."
	./test
	cd - > /dev/null
}

function build_and_test_all()
{
	for(( i=0; i<${#crypto_list[@]}; i++)) do
		echo ""
		build_and_test_crypto ${crypto_list[i]}
		echo ""
	done;
}

echo "build and test all crypto ..."

build_and_test_all

echo "build and test all crypto ... done"
