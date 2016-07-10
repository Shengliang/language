# Reference: https://www.ibm.com/developerworks/library/l-awk1/
awk '{ print }' /etc/passwd
awk '{ print $0 }' /etc/passwd
awk -F":" '{print $1 } ' /etc/passwd
cat num.txt | awk ' /^[0-9]+/ {print ($1^2)+1 }'
cat student.txt | awk ' !/[A-Z] [0-9]+ [0-9]+ [0-9]+/ { print "Not all scores are available for " $1 }'
cat s2.txt | awk '/[A-Z] [0-9]+ [0-9]+ [0-9]+/ { if ( $2 < 50 || $3 < 50  || $4 < 50 ) { print $1" : Fail" } else { print $1" : Pass"} }'
cat t.txt | cut -d"" -f2-7
