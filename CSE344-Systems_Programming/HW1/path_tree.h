#ifndef PATH_TREE_H
#define PATH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct N_Ary_Node{
	char *filename;
	struct N_Ary_Node *next;
	struct N_Ary_Node *child;
}N_Ary_Node;

void add_element(N_Ary_Node **root, char *path);
void traverse_tree(N_Ary_Node *root, int depth);
void free_tree(N_Ary_Node **root);

#endif
