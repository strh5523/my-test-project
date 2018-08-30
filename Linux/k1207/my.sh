#!/bin/bash
#变量  本地变量  环境变量 参数变量
# 大小4095
#str=$(ls)
#cd /usr/bin
str=`ls`
for i in $str
	do
		echo "i=$i"
	#	sleep 1
		done
#死循环
i=1
while [ : ]
do
echo "hello"
if [ "$i" -ge "3" ]
	then
	break
	fi
#i++
	#let "i+=1"
	i=`expr $i + 1`
	sleep 1
done
until [ -f a.c ]
do
echo "not find a.c"
sleep 1
done
#str='hello world'
#val=100
#printf "input:"
#read line
#if [ "$line" -ge "90" ] && [ "$line" -le "100" ]
#	then
#	echo "A"
#elif [ "$line" -ge "80" ] && [ "$line" -lt "90" ]
#then
#	echo "B"
#elif [ "$line" -ge "70" ] && [ "$line" -lt "80" ]
#then
#	echo "C"
#elif [ "$line" -ge "60" ] && [ "$line" -lt "70" ]
#then
#	echo "D"
#elif [ "$line" -ge "0" ] && [ "$line" -lt "60" ]
#then
#	echo "E"
#else
 
#	echo "$line not exist!"
#fi
#MYSTR=$val

#read 从键盘获取
#read line
#echo "str=$str"
#echo "val=$val"
#echo "MYSTR=$MYSTR"
#echo "line=$line"

#echo "\$1=$1"
#echo "\$*=$*"
#echo "PATH=$PATH"

exit 0
