#include "VariableTable.h"

VariableTable theTable;

void initTable() {
	theTable.size		= 0;
	theTable.capacity	= 2;
	theTable.data		= (Variable*)malloc(sizeof(Variable) * 2);
}

int indexOf(char* name) {
	for(int i=0 ; i < theTable.size ; i++)
		if(strcmp(theTable.data[i].name, name) == 0) //  if variable in symbol table
			return i;
	return -1;
}

Variable getByName(char* name) {
	int index = indexOf(name);

	if(index != -1)
		return theTable.data[index];

	Variable v;
	strcpy(v.name, name);
	v.value = -1;

	return v;
}

void addVariable(char* name, int value) {
	int index = indexOf(name);

	if( index == -1){

		if(theTable.size >= theTable.capacity){
			theTable.capacity	*= 2;
			theTable.data		= (Variable*) realloc (theTable.data, sizeof(Variable) * theTable.capacity);
		}

		strcpy(theTable.data[theTable.size].name, name);
		theTable.data[theTable.size].value = value;
		theTable.size += 1;
	}
	else{
		theTable.data[index].value = value;
	}
}
