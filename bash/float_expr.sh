#!/bin/bash
# bash float_expr.sh 
num=3.1415926
# bc does not carry correctly.
echo "scale = 3; $num/1.0 " | bc -l
# use printf to fix it.
printf "%.3f\n" $(echo "scale = 4; $num " | bc -l)
expr="5+50*3/20 + (19*2)/7"
echo "scale = 5; $expr " | bc -l
echo "scale = 4; $expr " | bc -l
echo "scale = 3; $expr " | bc -l
printf "%.3f\n" $(echo "scale = 4; $expr*1.0 " | bc -l)
