import sys
import re
s=input()
if s:
  m = re.search(r'(?=(\w)(.*?)(\1))', s)
  if m:
      a=m.group(1)
      b=m.group(3)
      if a and b and a == b :
        print(a)
      else:
        print(-1)
  else:
        print(-2)
  print("-" * 32)
  for x in re.split('[.,]', s) :
     if x:
       print(x)


    iterator=re.finditer("(?=(%s))" % ms, s)
    if iterator:
       for match in iterator:
           a = (match.start(1), match.end(1)-1)
           print(a)
    else:
        print(a)
