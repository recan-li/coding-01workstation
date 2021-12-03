#! /bin/bash -e

function get_os()
{
	echo "begin to get OS ..."

 	os=`uname -a | grep Darwin`
	if [ "$os" != "" ]; then
		host_os_name=OSX
	else
		os=`uname -a | grep x86_64`
		if [ "$os" != "" ]; then
			host_os_name=Linux64
		else
			host_os_name=Linux32
		fi
	fi

	echo "get OS name: $host_os_name"
}

function do_other_things()
{	
	echo "do other things ..."
}

get_os

do_other_things

exit 0