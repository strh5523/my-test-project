#!/bin/bash

fun()
{
#$1第一个参数 $#参数个数
	echo "fun run"
	echo "\$1=$1"
	echo "\$2=$2"
	local mystr=helloworld
	echo "fun:mystr=$mystr"
#	unset mystr
	return 3
}
fun "hello" "abc"
echo "fun=$?"
#val=$?
#echo "$val"
echo "main run:$$"
MYSTR="hello^_^"
#export MYSTR
#./test.sh
source /home/rh/Linux/k1214/test.sh
#. ./test.sh
#echo "\$#=$#"
#echo "\$1=$1"
#echo "main:mystr=$mystr"

#echo "input"
#read line

#case "$line" in
#[Yy][Ee][Ss] | [yY] ) echo"this is yes";;
#	yes ) echo "this is yes " ;;
#	no ) echo "this is no" ;;
#	* ) echo "****" ;;
#	esac

