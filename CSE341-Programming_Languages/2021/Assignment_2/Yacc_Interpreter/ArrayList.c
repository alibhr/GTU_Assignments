#include "ArrayList.h"

void* initArrayList(){
	ArrayList* theList = (ArrayList*)malloc(sizeof(ArrayList));

	theList->size		= 0;
	theList->capacity	= 1;
	theList->data		= (int*) malloc (sizeof(int) * 2);

	return theList;
}

void* addToList(void* list, int item){
	if(list == NULL)
		list = initArrayList();

	ArrayList * newList = list;

	if(newList->size == newList->capacity){
		newList->capacity *= 2;
		newList->data = (int*) realloc (newList->data, sizeof(int) * newList->capacity);
	}

	newList->data[newList->size] = item;
	newList->size += 1;

	return newList;
}

void* concat(void* _list1, void* _list2){
	ArrayList* list;
	ArrayList* result = initArrayList();

	if(_list1 != NULL){

		list = _list1;

		for(int i=0 ; i < list->size ; i++)
			addToList(result, list->data[i]);
	}

	if(_list2 != NULL){

		list = _list2;

		for(int i=0 ; i < list->size ; i++)
			addToList(result, list->data[i]);
	}

	return result;
}

ArrayList* append(void* _list, int item){
	ArrayList* list;
	ArrayList* result = initArrayList();

	addToList(result, item);

	if(list != NULL){

		list = _list;

		for(int i=0 ; i < list->size ; i++)
			addToList(result, list->data[i]);
	}

	return result;
}

void printList(void* _list, FILE* ostream){
	ArrayList* iter;

	if(_list == NULL){
		fprintf(ostream, "NULL\n");
	}
	else {
		iter = _list;

		if(iter->size == 0)
			fprintf(ostream, "NULL\n");

		else {
			fprintf(ostream, "(");

			for(int i=0 ; i < iter->size ; i++) {
				fprintf(ostream, "%d", iter->data[i]);

				if(i < iter->size - 1)
					fprintf(ostream, " ");
			}

			fprintf(ostream, ")\n");
		}
	}
}
