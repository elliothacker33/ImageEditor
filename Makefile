# Set gcc as the C++ compiler
CXX=g++

# Enforce C++ 2011 as the language standard
CXXFLAGS=-std=c++11 -pedantic

# Enable all standard warnings, uninitialized variable warnings, 
# and treat all warnings as errors
CXXFLAGS+= -Wall -Wuninitialized -Werror

# Generate code with debugging information
# (for use with a debugger like gdb)
CXXFLAGS+= -g 


# Enable ASan (Address Sanitizer) 
# and UBSan (Undefined Behavior Sanitizer)
#
# NOTE: comment these temporarily if 
# your development environment is failing
# due to these settings - it is important that 
# you fix your environment at some point.
CXXFLAGS+= -fsanitize=address -fsanitize=undefined


SRC = src
INCLUDE = include
TEST = test


CXXFLAGS+=-I $(INCLUDE) 

# C++ source files to consider in compilation for all programs
COMMON_CPP_FILES= $(SRC)/Color.cpp $(SRC)/Image.cpp $(SRC)/Script.cpp $(SRC)/PNG.cpp $(SRC)/XPM2.cpp

# C++ header files to consider in compilation
HEADERS= $(INCLUDE)/Color.hpp $(INCLUDE)/Image.hpp $(INCLUDE)/Script.hpp $(INCLUDE)/PNG.hpp $(INCLUDE)/XPM2.hpp 

PROGRAMS=runscript test

all: $(PROGRAMS)


runscript:  $(HEADERS) $(COMMON_CPP_FILES) $(SRC)/runscript.cpp
	$(CXX) -o runscript $(SRC)/runscript.cpp $(COMMON_CPP_FILES) $(CXXFLAGS)

test:  $(HEADERS) $(COMMON_CPP_FILES) $(SRC)/test.cpp
	$(CXX) -o test $(SRC)/test.cpp $(COMMON_CPP_FILES) $(CXXFLAGS)

clean: 
	rm -fr *.dSYM $(PROGRAMS)
