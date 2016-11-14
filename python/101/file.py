# Echo the contents of a file
f = open('file.py', 'rU')
for line in f:   ## iterates over the lines of the file
  print line,    ## trailing , so print does not add an end-of-line char
                 ## since 'line' already includes the end-of line.
f.close()
