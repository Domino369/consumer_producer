#
#  AUTHOR:    David Storme
#

# Variables
CC      = g++
CCFLAGS = -pthread -std=c++11 -Wall

# Rule to link object code files to create executable file
all: main.o factory.o product.o
	$(CC) $(CCFLAGS) -o ../build/factory main.o factory.o product.o

# Rules to compile source code files to object code
main.o: main.cpp factory.h product.h
	$(CC) $(CCFLAGS) -c main.cpp
	
factory.o: factory.cpp factory.h product.h
	$(CC) $(CCFLAGS) -c factory.cpp

product.o: product.cpp product.h
	$(CC) $(CCFLAGS) -c product.cpp
	
# Pseudo-target to remove object code and executable files
clean:
	-rm *.o
