#!/usr/bin/env python
# import modules used here -- sys is a very standard one
import sys

# Gather our code in a main() function
def main():
    # Command line args are in sys.argv[1], sys.argv[2] ...
    # sys.argv[0] is the script name itself and can be ignored
    argc = len(sys.argv)
    name = "who?"
    if (argc > 1) :
       name = sys.argv[1]
    print 'Hello there, ', name

# Standard boilerplate to call the main() function to begin
# the program.
if __name__ == '__main__':
    main()
