# http://stackoverflow.com/questions/3112687/how-to-iterate-over-associative-array-in-bash
n=0
while read input
do
    myarray["${n}"]=${input}
    echo "${n}"
    n+=1
    # $((n=n+1))
done

for i in "${!myarray[@]}"
do 
   echo "key  : $i"
   echo "value: ${myarray[$i]}"
done

echo "${myarray[@]:3:5}"
echo "${myarray[@]:9:5}"
echo "${myarray[@]:10:5}"
