import sys
tuple = (1, 2, 'hi')
print len(tuple)  ## 3
print tuple[2]    ## hi
try :
  tuple[2] = 'bye'
except TypeError as e:
  print "Type error:",e
except IOError as e:
  print "I/O error({0}): {1}".format(e.errno, e.strerror)
except RuntimeError as e:
  print "Runtime error({0}): {1}".format(e.errno, e.strerror)
except NameError as e:
  print "Name error({0}): {1}".format(e.errno, e.strerror)
except ValueError as e:
  print "Value error({0}): {1}".format(e.errno, e.strerror)
except:
  print "Unexpected error:", sys.exc_info()[0]
tuple = (1, 2, 'bye')  ## this works

# https://docs.python.org/2/tutorial/errors.html
