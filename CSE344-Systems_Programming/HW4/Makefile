#OBJS specifies which files to compile as part of the project
OBJS = 171044066.c queue.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -lrt -pthread -Wall -Wextra -Wshadow -pedantic -pedantic-errors -ansi -std=gnu99 -pthread # -O3 --save-temps

#	-Wall -Wextra: reasonable and standard
#	-Wshadow: warn the user if a variable declaration shadows another with the same name in the same scope
#	-pedantic: warn about non-portable code, C++ that uses language extensions.

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = program

#This is the target that compiles our executable
all :	$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
	# ./$(OBJ_NAME)
