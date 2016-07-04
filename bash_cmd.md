
# Display every character in a word  in new line
echo SHENGLIANG | fold -w 1
echo SHENGLIANG | sed -e 's/./&\n/g' | grep -v '\B'

# count letter frequency and sort frequncy counters in reverse order (from big to small) 
echo SHENGLIANG | fold -w 1 | sort | uniq -c  | sort -rn

# Find the current directory name.
pwd | tr [\/] [\\n] | tail -n1
basename `pwd`

# Ref: http://sed.sourceforge.net/sed1line.txt
# Find the highest time difference in the below log file.
# https://www.careercup.com/question?id=5685801251766272
# STARTTIME:YYYY-MM-DD HH:MM:SS 
# ENDTIME :YYYY-MM-DD HH:MM:SS 
# -----------------------------
# -----------------------------
# STARTTIME:2015-12-01 04:13:15 
# ENDTIME :2015-12-01 04:14:16 
# ---------------------------------------------- 
# ---------------------------------------------- 
# STARTTIME:2015-12-01 04:11:15 
# ENDTIME :2015-12-01 04:11:17 
# ---------------------------------------------- 
# ---------------------------------------------- 
# STARTTIME:2015-12-01 04:12:15 
# ENDTIME :2015-12-01 04:15:15 
# ---------------------------------------------- 
# ---------------------------------------------- 
# STARTTIME:2015-12-01 04:10:10 
# ENDTIME :2015-12-01 04:10:11 
# ---------------------------------------------- 
# ----------------------------------------------
cat input.txt | grep -v "^-"  | cut -d: -f2- |  sed 's/....-..-.. ..:..:../date +%s --date="&"/e'  | sed '$!N;s/\n/ /' | sed  's/\(.\{10\}\) \(.\{10\}\)/echo \$((\2 - \1))/e'  | sort -rn | head -n 1
# Include input data as well.
cat input.txt | grep -v "^-"   | sed '$!N;s/\n//' | sed 's/STARTTIME:\(....-..-.. ..:..:..\) ENDTIME :\(....-..-.. ..:..:..\)/echo \$(( $(date +%s --date="\2") - $(date +%s --date="\1") )) ENDTIME:\2 - STARTTIME:\1 /e' | sort -rn | head -n 1
