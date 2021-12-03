#! /bin/bash -e

function get_os()
{
	echo "begin to get OS ..."

	osx_name=Darwin
	linux64_name=x86_64
	if [ "`uname -a | grep $osx_name`" != "" ]; then
		host_os_name=OSX
	elif [ "`uname -a | grep $linux64_name`" != "" ]; then
		host_os_name=Linux64
	else
		host_os_name=Linux32		
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