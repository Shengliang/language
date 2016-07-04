# Reference: https://www.ibm.com/developerworks/library/l-awk1/
awk '{ print }' /etc/passwd
awk '{ print $0 }' /etc/passwd
awk -F":" '{print $1 } ' /etc/passwd
cat num.txt | awk ' /^[0-9]+/ {print ($1^2)+1 }'


