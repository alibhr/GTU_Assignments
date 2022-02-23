#ifndef VARIABLE_TABLE_H
#define VARIABLE_TABLE_H

#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 36

typedef struct Variable {
	char	name[MAX_NAME_SIZE];
	int		value;
} Variable ;

typedef struct VariableTable {
	Variable*	data;
	int			size;
	int			capacity;
} VariableTable ;

void initTable();
int indexOf(char* name);
Variable getByName(char* name);
void addVariable(char* name, int value);

#endif
