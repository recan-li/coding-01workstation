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

# open debug option
set -xv

get_os

# close debug option
set +xv

# re-open debug option
set -xv

do_other_things

# close debug option
set +xv

exit 0