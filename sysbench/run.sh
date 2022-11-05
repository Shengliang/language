#!/bin/bash

n=100
for (( i=10 ; i<=$n ; i=i+10 ));
do
    ./wr.sh $i
   # ./ro.sh $i
done

