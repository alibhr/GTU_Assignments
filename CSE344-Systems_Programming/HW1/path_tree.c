#include "path_tree.h"

void n_copy(char *str1, char *str2, int n);

void add_element(N_Ary_Node **root, char *path){

	if(*path == '\0')
		return;

	int i=0;
	for(i=0 ; path[i]!='\0' && path[i]!='/' ;++i);

	char *f_name = (char*)malloc(sizeof(char)* (i + 2));
	if(f_name == NULL) fprintf(stderr, "malloc error at add_element\n");

	if(i == 0){
		f_name[0] = '/';
		f_name[1] = '\0';
	}
	else{
		n_copy(f_name, path, i);
	}

	if(*root == NULL){
		*root = (N_Ary_Node*)malloc(sizeof(N_Ary_Node));
		if(root == NULL) fprintf(stderr, "malloc error at add_element\n");

		(*root)->filename = f_name;
		(*root)->next = NULL;
		(*root)->child = NULL;

		if(path[i] != '\0')
			add_element(&((*root)->child), path+i+1);

		return;
	}

	N_Ary_Node *iter = *root;
	while(iter->next != NULL){
		if(!strcmp(f_name, iter->filename)){
			free(f_name);
			if(path[i] == '\0') return;
			add_element(&iter->child, path+i+1);
			return;
		}
		iter = iter->next;
	}

	if(!strcmp(f_name, iter->filename)){
		free(f_name);
		if(path[i] == '\0') return;
		add_element(&iter->child, path+i+1);
		return;
	}

	iter->next = (N_Ary_Node*)malloc(sizeof(N_Ary_Node));
	if(iter->next == NULL) fprintf(stderr, "malloc error at add_element\n");

	iter->next->filename = f_name;
	iter->next->next=NULL;
	iter->next->child = NULL;

	if(path[i] != '\0')
		add_element(&(iter->next->child), path+i+1);
}

void traverse_tree(N_Ary_Node *root, int depth){
	if(root == NULL)
		return;

	fprintf(stdout, "|");
	for(int i=0 ; i<depth ; ++i) fprintf(stdout, "--");
	fprintf(stdout, "%s\n", root->filename);


	if(root->child != NULL)
		traverse_tree(root->child, depth+1);

	if(root->next != NULL)
		traverse_tree(root->next, depth);
}

void free_tree(N_Ary_Node **root){
	if(*root == NULL)
		return;

	if((*root)->child != NULL)
		free_tree(&((*root)->child));

	if((*root)->next != NULL)
		free_tree(&((*root)->next));

	free((*root)->filename);
	free(*root);
}

void n_copy(char *str1, char *str2, int n){

	int i=0;
	for(i=0 ; i<n && str2[i] != '\0' ; ++i){
		str1[i] = str2[i];
	}
	str1[i] = '\0';
}
