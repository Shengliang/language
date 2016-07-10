#!/bin/bash

while read line
do
    my_array=("${my_array[@]}" $line)
done

echo All array elements: ${my_array[@]}
sz=${#my_array[*]}
echo Array Size: ${sz}
echo "Sub array from [3 to 7)"
for ((I=3; I < 7 && I < sz; I++))
{
   echo -n "${my_array[$I]} "
}


