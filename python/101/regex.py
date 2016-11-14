import re
str = 'an example word:cat!!'
match = re.search(r'word:\w\w\w', str)
# If-statement after search() tests if it succeeded
if match:                      
  print 'found', match.group() ## 'found word:cat'
else:
  print 'did not find'

## Search for pattern 'iii' in string 'piiig'.
## All of the pattern must match, but it may appear anywhere.
## On success, match.group() is matched text.
match = re.search(r'iii', 'piiig') 
print match.group() == "iii"
match = re.search(r'igs', 'piiig') 
print match == None

## . = any char but \n
match = re.search(r'..g', 'piiig') 
print match.group() == "iig"

## \d = digit char, \w = word char
match = re.search(r'\d\d\d', 'p123g') 
print match.group() == "123"
match = re.search(r'\w\w\w', '@@abcd!!') 
print match.group() == "abc"
