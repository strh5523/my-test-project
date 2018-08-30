#!/bin/bash
 
 echo "input src file"
 read line1
 echo "inptu des file"
 read line2
#$1第一列 $2第二列 -F指定分割符
awk -F: '{print $1}' "$line1" > "$line2"
