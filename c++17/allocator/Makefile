
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Source files
# SRCS = memory_management.cpp
SRCS = ex1.cpp ex2.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: ex1 ex2

# Link the object files to create the executable
ex1: ex1.o
	$(CXX) $(CXXFLAGS) -o $@ $@.o

ex2: ex2.o
	$(CXX) $(CXXFLAGS) -o $@ $@.o

ex3: ex3.o
	$(CXX) $(CXXFLAGS) -o $@ $@.o

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) ex1 ex2

# Phony targets
.PHONY: all clean
