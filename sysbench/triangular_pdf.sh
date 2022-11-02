#!/bin/bash

# https://web.mit.edu/urban_or_book/www/book/chapter7/7.1.3.html
# [0-1]
# 2*x^2 , 4x-2*x^2 - 1
# 0.5   0.5
# 1     1
function f {
    local x=$(($1%200))
    if [[ $x -lt 50 ]]
    then
      #echo -n "2*x^2 $i "
      echo -n "$i "
      v=`echo "scale=3;2*($x/100.0)*($x/100.0)*1000" | bc`
      echo "($v + 0.5)/1" | bc
    elif  [[ $x -lt 150 ]]
    then
      # echo -n "4x-2*x^2-1 $i "
      echo -n "$i "
      v=`echo "scale=3;(4*($x/100.0) - 2*($x/100.0)*($x/100.0) - 1)*1000"  | bc`
      echo "($v + 0.5)/1" | bc
    else
      # echo -n "2*(x-2)^2 $i "
      echo -n "$i "
      v=`echo "scale=3;2*(($x-200)/100.0)*(($x-200)/100.0)*1000" | bc`
      echo "($v + 0.5)/1" | bc
    fi
}
n=1000
for (( i=0; i<$n ; i=i+1 ));
do
   f $i
done
