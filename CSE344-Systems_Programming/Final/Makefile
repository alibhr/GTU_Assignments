#OBJS specifies which files to compile as part of the project
OBJS_SERVER = server.c queue.c
OBJS_CLIENT = client.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -lrt -pthread -Wall -Wextra -Wshadow -pedantic -pedantic-errors -ansi -std=gnu99 -pthread # -O3 --save-temps

#	-Wall -Wextra: reasonable and standard
#	-Wshadow: warn the user if a variable declaration shadows another with the same name in the same scope
#	-pedantic: warn about non-portable code, C++ that uses language extensions.

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME_SERVER = server
OBJ_NAME_CLIENT = client

#This is the target that compiles our executable
all :	$(OBJS_SERVER) $(OBJS_CLIENT)
	$(CC) $(OBJS_SERVER) $(COMPILER_FLAGS) -o $(OBJ_NAME_SERVER)
	$(CC) $(OBJS_CLIENT) $(COMPILER_FLAGS) -o $(OBJ_NAME_CLIENT)
