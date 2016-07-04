# Find maximum and minimum values present in column 1
# awk -f find_max_min.awk num.txt
NR == 2 {m=$1 ; p=$1}
$1 >= m {m = $1}
$1 <= p {p = $1}
END { print "Max = " m, "   Min = " p }
