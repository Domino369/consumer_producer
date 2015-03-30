#
#  AUTHOR:    David Storme
#

# Variables
CC      = g++
CCFLAGS = -pthread -std=c++11 -Wall

# Rule to link object code files to create executable file
all:
	cd src; make
	
# Pseudo-target to remove object code and executable files
clean:
	cd src; make clean
	cd build; rm *
