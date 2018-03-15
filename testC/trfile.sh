#!/bin/sh
#tr file
FILES=""
TRCASE=""
EXT=""
OPT=""

err_msg()
{
_FIREWARE=$1
echo "'basename $0'":Error the conversion failed on $_FIREWARE"
}

if [ $# -eq 1 ];then
	echo "for more info try 'basename $0' --help"
	exit 1
fi

while [ $# -gt 0 ]
do
	case $1 in
	-u)
		TRCASE=upper
		EXT=".UC"
		OPT=yes
		shift;;
	-l)
		TRACE=lower
		EXT="-LC"
		OPT=yes
		shift;;
	-*)
		echo "usage: 'basename #0' -[l|u] file [file..]"
		exit 0;;
	*)	
		if [ -f $1 ];then
			FILES= $FILES" "$1
		else
			echo "'basename $0':Error cannot find the file $1"
		fi
		shift;;
	esac
done

#no option given
if [ $OPT = "no" ];then
	echo "'basename $0':Error you need to specify an option.No action taken"
	echo "try 'basename $0' --help"
fi	
	
#now read in all the file
for LOOP in $FILES
do
	case $TRACE in
		lower)
		cat $LOOP | tr "[a-z]" "[A-Z]" > $LOOP$EXT
		if [ $?= 0 ];then
			err_msg $LOOP
		else
			echo "convered file called $LOOP$EXT
		fi;;
		upper)
		cat $LOOP | tr "[A-Z]" "[a-z]" $LOOP$EXT
		if [ $?!=0 ];then
			err_msg $LOOP
		else
			echo 'convered file called $LOOP$EXT
		fi
	esac
done