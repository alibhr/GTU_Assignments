#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayList {
	int*	data;
	int		size;
	int		capacity;
} ArrayList ;

void* initArrayList();
void* addToList(void* list, int item);
void* concat(void* _list1, void* _list2);
ArrayList* append(void* _list, int item);
void printList(void* _list, FILE* ostream);

#endif
