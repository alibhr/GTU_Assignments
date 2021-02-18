#OBJS specifies which files to compile as part of the project
OBJS = main.cpp GTUVector.cpp GTUIterator.cpp GTUIteratorConst.cpp GTUSet.cpp 

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic --std=c++11

#	-Wall -Wextra: reasonable and standard
#	-Wshadow: warn the user if a variable declaration shadows another with the same name in the same scope
#	-Wnon-virtual-dtor: warn the user if a class with virtual functions has a non-virtual destructor. This can lead to hard to track down memory errors
#	-pedantic: warn about non-portable code, C++ that uses language extensions.

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = a.out

#This is the target that compiles our executable
all :	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
#	./$(OBJ_NAME)
