#!/bin/bash

i=1;
while [ : ]
do
	read str
if [ "$str" -eq "123456" ]
	then
	echo "success"
	break
elif [ "$i" -eq "3" ]
then
echo "failed3times"
break
fi
i=`expr $i + 1`
done
