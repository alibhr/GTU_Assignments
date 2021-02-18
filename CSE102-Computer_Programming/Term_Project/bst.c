#include <stdio.h>
#include <stdlib.h>

typedef struct Tree{
	int data;
	struct Tree *right;
	struct Tree *left;
}Tree;

Tree* insert(Tree *root,int data);
void traverse(Tree *root);
int findDepthOfTree(Tree *root);
void freeTree(Tree **root);

int main(){
	Tree *root = NULL;
	root=insert(root,50);
	root=insert(root,100);
	root=insert(root,150);
	root=insert(root,200);
	root=insert(root,125);
	root=insert(root,140);
	root=insert(root,135);
	root=insert(root,130);
	root=insert(root,132);
	root=insert(root,30);
	root=insert(root,20);
	root=insert(root,21);
	root=insert(root,22);


	//traverse(root);
	printf("depth : %d\n",findDepthOfTree(root));

	freeTree(&root);
	return 0;
}

Tree* insert(Tree *root,int data){
	if(root==NULL){
		root=(Tree*)malloc(sizeof(Tree));
		root->data=data;
		root->right=NULL;
		root->left=NULL;
		return root;
	}
	if(data > root->data){
		root->right=insert(root->right,data);
		return root;
	}
	else if(data < root->data){
		root->left=insert(root->left,data);
		return root;
	}
	else{
		printf("element couldn't be added (%d has been already exist in tree)\n",root->data);
		return root;
	}
}

void traverse(Tree *root){
	if(root==NULL){
		return;
	}
	traverse(root->left);
	printf("%d\n",root->data);
	traverse(root->right);
}

int findDepthOfTree(Tree *root){
	int r,l;

	if(root == NULL)
		return 0;

	if((r=(1 + findDepthOfTree(root->right))) > (l=(1 + findDepthOfTree(root->left)))){
		return r;
	}
	else{
		return l;
	}
}

void freeTree(Tree **root){
	if(root == NULL)
		return;

	if((*root)->left != NULL)
		freeTree(&((*root)->left));

	if((*root)->right != NULL)
		freeTree(&((*root)->right));

	free((*root));

}
