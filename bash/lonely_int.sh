#!/bin/bash
#Find the lonely int in an array.
# cat lonely_int.txt | ./lonely_int.sh
read -r LIMIT
x="0"
read -a arr
for n in ${arr[@]}
do
   x=$(( $n ^ $x ))
done

echo $x
