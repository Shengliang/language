#!/bin/bash
declare -A matrix
read N
num_rows=63
num_columns=100

for ((i=0;i<num_rows;i++)) do
    for ((j=0;j<num_columns;j++)) do
        matrix[$i,$j]='_'
    done
done

function printn
{
  local r=$(($num_rows-$1-1))
  local A=$2
  local I=$3
  local H=$4
  local c=0
  c=$(($A - $I - 1))
  matrix[$r,$c]="1"
  c=$(($A + $I - 1))
  matrix[$r,$c]="1"
}

function print_Y
{
   local s=$1
   local H=$2
   local A=$3
   local N=$4
   for ((I=0; I < H; I++))
   {
       printn $(($s+$I)) $A 0
   }
   for ((I=1; I <= H; I++))
   {
       printn $(($s+$H+$I-1)) $A $I $H
   }
   if [ "$H" -gt "0" ] && [ "$N" -gt "1" ]; then
     print_Y $((s+$H*2)) $(($H/2)) $(($A-$H)) $(($N-1))
     print_Y $((s+$H*2)) $(($H/2)) $(($A+$H)) $(($N-1))
   fi
}

print_Y 0 16 50 $N 

for ((i=0;i<num_rows;i++)) do
    for ((j=0;j<num_columns;j++)) do
        printf ${matrix[$i,$j]}
    done
    printf "\n"
done
