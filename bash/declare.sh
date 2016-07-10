#!/bin/bash
# . declare.sh
# bash declare.sh  

function bar
{
echo "In function bar."
echo "Arguments:"
echo $1 $2 $3 $4 $5 $6 $7 $8 $9 $10 $11
}

function sum
{
BEGIN=$1
END=$2
for ((a= BEGIN; a <= END ; a++))
do
  echo -n "$a "
done
}

foo()
{
echo "In function foo."
declare -i number
number=3
number=number+1
echo "number incremented by 1 is $number."

declare -a arr
arr=(`ls`)
echo "================================"
echo "number of elements in array:" ${#arr[*]}
echo ${arr[0]}
echo ${arr[1]}
echo ${arr[0]:2}
echo ${arr[1]:2}
sz=${#arr[*]}
for ((I=0; I < sz; I++))
{
   echo -n "$I "
   echo -n "length of ith element:" ${#arr[$I]} " "
   echo ${arr[$I]}
}
echo "================================"
for f in ${arr[@]}
do
  echo $f
done
echo "================================"
for f in *
do
  echo $f
done

echo "End"
}

declare -f foo

# Call the function
foo
bar a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12
sum 1 10
