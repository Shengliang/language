# http://stackoverflow.com/questions/16487258/how-to-declare-2d-array-in-bash
#!/bin/bash
declare -A matrix
num_rows=4
num_columns=5

for ((i=0;i<num_rows;i++)) do
    for ((j=0;j<num_columns;j++)) do
        matrix[$i,$j]=$RANDOM
    done
done

f1="%$((${#num_rows}+1))s"
f2=" %9s"

printf "$f1" ''
for ((i=0;i<num_rows;i++)) do
    printf "$f2" $i
done
echo

for ((j=0;j<num_columns;j++)) do
    printf "$f1" $j
    for ((i=0;i<num_rows;i++)) do
        printf "$f2" ${matrix[$i,$j]}
    done
    echo
done
