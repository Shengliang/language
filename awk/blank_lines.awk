# awk -f blank_lines.awk blank_lines.awk

BEGIN { cnt = 0 }

/^$/  { cnt = cnt + 1 }

END   { print "I found " cnt " blank lines." }
