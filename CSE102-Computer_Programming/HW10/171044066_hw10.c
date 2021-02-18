#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE_N 16
#define SIZE 20
typedef struct stack{
	int data;
	struct stack *next;
}stack;
typedef struct queue{
	int data;
	struct queue *next; 
}queue;
typedef struct bst{
	int data;
	struct bst *left;
	struct bst *right;
}bst;
void fill_structures(stack ** stack_,queue ** queue_, bst ** bst_,int data[20]);
void push(stack ** stack_,int data);
int pop(stack ** stack_);
void enqueue(queue ** queue_,int data);
int dequeue(queue ** queue_);
bst * fill_bst_r(bst * bst_,int data);
bst * fill_bst_i(bst * bst_,int data);

void ordered_print(stack * stack_,queue * queue_,bst * bst_);
void sort_stack_r(stack * stack_);
void sort_r_stack(stack ** stack_,int temp);
void sort_queue_r(queue * queue_);
void sort_r_queue(queue ** queue_,int temp);
void copy_queue(queue **q1,queue *q2);
void copy_stack_r(stack **s1,stack *s2);

void search(stack * stack_,queue * queue_,bst * bst_,int val_to_search);
void search_in_stack(stack * stack_,int val_to_search,stack *stack_s);
void search_in_queue(queue * queue_,int val_to_search,stack *stack_q);
void search_in_bst(bst * bst_,int val_to_search,stack *stack_t);

void special_traverse(stack * stack_, queue * queue_, bst * bst_);
void special_traverse_stack(stack * stack_);
int find_max_s(stack ** stack_);
int find_min_s(stack ** stack_);	
void special_traverse_queue(queue * queue_);
int find_max_q(queue ** queue_);
int find_min_q(queue ** queue_);
void special_traverse_bst(bst * bst_);

void print_stack(stack * stack_);
void print_queue(queue * queue_);
void print_bst(bst *bst_);
void report(double t_stack,double t_queue,double t_bst,char name[SIZE_N]);

int main(){
	int data[20]={5,2,7,8,11,3,21,7,6,15,19,35,24,1,8,12,17,8,23,4};
	bst *bst_;
	queue *queue_;
	stack *stack_;
	fill_structures(&stack_,&queue_,&bst_,data);
	ordered_print(stack_,queue_,bst_);
	search(stack_, queue_, bst_, 8);
	special_traverse(stack_, queue_, bst_);
	return 0;
}


void fill_structures(stack ** stack_,queue ** queue_, bst ** bst_,int data[20]){
	double t_stack,t_queue,t_bst;
	time_t start,end;
	int i=0;
	(*stack_)=NULL;
	(*queue_)=NULL;
	(*bst_)=NULL;

	start=clock();
	for(i=0;i<SIZE;i++){
		push(stack_,data[i]);
	}
	end=clock();
	t_stack=((double)(end-start))/CLOCKS_PER_SEC;


	start=clock();
	for(i=0;i<SIZE;i++){
		enqueue(queue_,data[i]);
	}
	end=clock();
	t_queue=((double)(end-start))/CLOCKS_PER_SEC;


	start=clock();
	for(i=0;i<SIZE;i++){
		(*bst_)=fill_bst_i((*bst_),data[i]);
	}
	end=clock();
	t_bst=((double)(end-start))/CLOCKS_PER_SEC;


	report(t_stack,t_queue,t_bst,"filling");
	printf("\n\n");
}
void push(stack ** stack_,int data){
	if((*stack_)==NULL){
		(*stack_)=(stack*)malloc(sizeof(stack));
		(*stack_)->data=data;
		(*stack_)->next=NULL;
	}
	else{
		stack *new=(stack*)malloc(sizeof(stack));
		new->data=data;
		new->next=(*stack_);
		(*stack_)=new;
	}
}
int pop(stack ** stack_){
	if((*stack_)==NULL){
		printf("Empty\n");
		return -1;
	}
	int t=(*stack_)->data;
	stack *temp=(*stack_);
	(*stack_)=(*stack_)->next;
	free(temp);
	return t;
}
void enqueue(queue ** queue_,int data){
	if((*queue_)==NULL){
		(*queue_)=(queue*)malloc(sizeof(queue));
		(*queue_)->data=data;
		(*queue_)->next=NULL;
	}
	else{
		queue *temp1=(*queue_);
		while((*queue_)->next!=NULL){
			(*queue_)=(*queue_)->next;
		}
		queue *new=(queue*)malloc(sizeof(queue));
		new->data=data;
		new->next=NULL;
		(*queue_)->next=new;
		(*queue_)=temp1;
	}
}
int dequeue(queue ** queue_){
	if((*queue_)==NULL){
		printf("Empty\n");
		return -1;
	}
	int t=(*queue_)->data;
	queue *temp=(*queue_);
	(*queue_)=(*queue_)->next;
	free(temp);
	return t;
}
bst * fill_bst_r(bst * bst_,int data){
	if(bst_==NULL){
		bst_=(bst*)malloc(sizeof(bst));
		bst_->data=data;
		bst_->right=NULL;
		bst_->left=NULL;
		return bst_;
	}
	if(data > bst_->data){
		bst_->right=fill_bst_r(bst_->right,data);
		return bst_;
	}
	if(data <= bst_->data){
		bst_->left=fill_bst_r(bst_->left,data);
		return bst_;
	}
}
bst * fill_bst_i(bst *bst_,int data){
	if(bst_==NULL){
		bst_=(bst*)malloc(sizeof(bst));
		bst_->data=data;
		bst_->right=NULL;
		bst_->left=NULL;
		return bst_;
	}
	bst *temp=bst_;
	while(temp!=NULL){
		if(data > temp->data){
			if(temp->right==NULL){
				temp->right=(bst*)malloc(sizeof(bst));
				temp->right->data=data;
				temp->right->left=NULL;
				temp->right->right=NULL;
				break;
			}
			temp=temp->right;
		}
		else{
			if(temp->left==NULL){
				temp->left=(bst*)malloc(sizeof(bst));
				temp->left->data=data;
				temp->left->left=NULL;
				temp->left->right=NULL;
				break;
			}
			temp=temp->left;
		}
	}
	return bst_;
}


void ordered_print(stack * stack_,queue * queue_,bst * bst_){
	stack *temp_stack=NULL;
	queue *temp_queue=NULL;
	copy_stack_r(&temp_stack,stack_);
	copy_queue(&temp_queue,queue_);

	double t_stack,t_bst,t_queue;
	time_t start,end;

	printf("stack-->");
	start=clock();
	sort_stack_r(temp_stack);
	print_stack(temp_stack);
	end=clock();
	t_stack=((double)(end-start))/CLOCKS_PER_SEC;

	printf("queue-->");
	start=clock();
	sort_queue_r(temp_queue);
	print_queue(temp_queue);
	end=clock();
	t_queue=((double)(end-start))/CLOCKS_PER_SEC;

	printf("tree-->");
	start=clock();
	print_bst(bst_);
	printf("\n");
	end=clock();
	t_bst=((double)(end-start))/CLOCKS_PER_SEC;



	report(t_stack,t_queue,t_bst,"ordering and printing");
	printf("\n\n");
}
void sort_stack_r(stack * stack_){
	if(stack_==NULL){
		return;
	}
	int temp=pop(&stack_);
	sort_stack_r(stack_);
	sort_r_stack(&stack_,temp);
	/*
	if(stack_!=NULL){
		int temp=pop(&stack_);
		sort_stack(stack_);
		sort_r_stack(&stack_,temp);
	}*/
}
void sort_r_stack(stack ** stack_,int temp){
	if((*stack_)==NULL || temp > (*stack_)->data){
		push(stack_,temp);
		return;
	}
	int temp1=pop(stack_);
	sort_r_stack(stack_,temp);
	push(stack_,temp1);
}
void sort_queue_r(queue * queue_){
	if(queue_==NULL){
		return;
	}
	int temp=dequeue(&queue_);
	sort_queue_r(queue_);
	sort_r_queue(&queue_,temp);	
}
void sort_r_queue(queue ** queue_,int temp){
	if((*queue_)==NULL || temp > (*queue_)->data){
		queue *new=(queue*)malloc(sizeof(queue));
		new->data=temp;
		new->next=(*queue_);
		(*queue_)=new;
		return;
	}

	int temp1=(*queue_)->data;
	queue *tempp=(*queue_);
	(*queue_)=(*queue_)->next;
	free(tempp);

	sort_r_queue(queue_,temp);

	queue *new=(queue*)malloc(sizeof(queue));
	new->data=temp1;
	new->next=(*queue_);
	(*queue_)=new;
}
void copy_stack_r(stack **s1,stack *s2){
	if(s2==NULL){
		return;
	}
	int temp=s2->data;
	copy_stack_r(s1,s2->next);
	push(s1,temp);
}
void copy_queue(queue **q1,queue *q2){
	if(q2==NULL){
		return;
	}
	int temp=q2->data;
	copy_queue(q1,q2->next);
	enqueue(q1,temp);
}


void search(stack * stack_,queue * queue_,bst * bst_,int val_to_search){
	time_t start,end;
	double t_stack,t_queue,t_bst;


	stack *stack_s=NULL;
	printf("stack(head)--->");
	print_stack(stack_);
	printf("number to search : %d\n",val_to_search);
	start=clock();
	search_in_stack(stack_,val_to_search,stack_s);
	end=clock();
	printf("\n");
	t_stack=((double)(end-start))/CLOCKS_PER_SEC;


	stack *stack_q=NULL;
	printf("queue(head)-->");
	print_queue(queue_);
	printf("number to search : %d\n",val_to_search);
	start=clock();
	search_in_queue(queue_,val_to_search,stack_q);
	end=clock();
	printf("\n");
	t_queue=((double)(end-start))/CLOCKS_PER_SEC;


	stack *stack_t=NULL;
	printf("tree-->");
	print_bst(bst_);
	printf("\nnumber to search : %d\n",val_to_search);
	start=clock();
	search_in_bst(bst_,val_to_search,stack_t);
	end=clock();
	printf("\n");
	t_bst=((double)(end-start))/CLOCKS_PER_SEC;


	report(t_stack,t_queue,t_bst,"search");
}
void search_in_stack(stack * stack_,int val_to_search,stack *stack_s){
	int step=0,total=0;
	while(stack_!=NULL){
		if(stack_!=NULL && stack_->data==val_to_search){
			push(&stack_s,step);
			total++;
		}
		step++;
		stack_=stack_->next;
	}

	printf("%d result found on ", total);
	while(stack_s!=NULL){
		printf("%d.step ",stack_s->data);
		stack_s=stack_s->next;
	}
	printf(".\n");
}
void search_in_queue(queue * queue_,int val_to_search,stack *stack_q){
	int step=0,total=0;
	while(queue_!=NULL){
		if(queue_->data==val_to_search){
			push(&stack_q,step);
			total++;
		}
		queue_=queue_->next;
		step++;
	}

	printf("%d result found on ", total);
	while(stack_q!=NULL){
		printf("%d.step ",stack_q->data);
		stack_q=stack_q->next;
	}
	printf(".\n");
}
void search_in_bst(bst * bst_,int val_to_search,stack *stack_t){
	int step=0,total=0;
	while(bst_!=NULL){
		if(val_to_search > bst_->data){
			bst_=bst_->right;
		}
		else if(val_to_search < bst_->data){
			bst_=bst_->left;
		}
		else if(val_to_search == bst_->data){
			push(&stack_t,step);
			bst_=bst_->left;
			total++;
		}
		step++;
	}
	printf("%d result found on ",total);
	while(stack_t!=NULL){
		printf("%d.step ",stack_t->data);
		stack_t=stack_t->next;
	}
	printf(".\n");
}


void special_traverse(stack * stack_, queue * queue_, bst * bst_){
	double t_stack,t_queue,t_bst;
	time_t start,end;

	printf("\n\nspecial traverse for stack -> ");
	start=clock();
	special_traverse_stack(stack_);
	end=clock();
	t_stack=((double)(end-start))/CLOCKS_PER_SEC;

	printf("\nspecial traverse for queue -> ");
	start=clock();
	special_traverse_queue(queue_);
	end=clock();
	t_queue=((double)(end-start))/CLOCKS_PER_SEC;

	printf("\nspecial traverse for tree -> \n");
	start=clock();
	special_traverse_bst(bst_);
	end=clock();
	t_bst=((double)(end-start))/CLOCKS_PER_SEC;
	printf("\n");
	report(t_stack,t_queue,t_bst,"special traverse");
}
void special_traverse_stack(stack * stack_){
	while(stack_!=NULL){
		printf("%d ",find_max_s(&stack_));
		printf("%d ",find_min_s(&stack_));
	}
	printf("\n");
}
void special_traverse_queue(queue * queue_){
	while(queue_!=NULL){
		printf("%d ",find_max_q(&queue_));
		printf("%d ",find_min_q(&queue_));
	}
	printf("\n");
}
void special_traverse_bst(bst * bst_){
}
int find_max_s(stack ** stack_){
	if((*stack_)==NULL){
		return 0;
	}
	int max=(*stack_)->data;
	stack *temp,*prev,*for_free;
	temp=(*stack_);

	while(temp->next!=NULL){
		if(max < temp->next->data){
			prev=temp;
			max=temp->next->data;
		}
		temp=temp->next;
	}
	if(max==(*stack_)->data){
		for_free=(*stack_);
		max=(*stack_)->data;
		(*stack_)=(*stack_)->next;
		free(for_free);
	}
	else{
 		for_free=prev->next;
		prev->next=prev->next->next;
		free(for_free);
	}
	return max;
}
int find_min_s(stack ** stack_){
	if((*stack_)==NULL){
		return 0;
	}
	int min=(*stack_)->data;
	stack *temp,*prev,*for_free;
	temp=(*stack_);

	while(temp->next!=NULL){
		if(min > temp->next->data){
			prev=temp;
			min=temp->next->data;
		}
		temp=temp->next;
	}
	if(min==(*stack_)->data){
		for_free=(*stack_);
		min=(*stack_)->data;
		(*stack_)=(*stack_)->next;
		free(for_free);
	}
	else{
 		for_free=prev->next;
		prev->next=prev->next->next;
		free(for_free);
	}
	return min;
}
int find_max_q(queue ** queue_){
	if((*queue_)==NULL){
		return 0;
	}
	int max=(*queue_)->data;
	queue *temp,*prev,*for_free;
	temp=(*queue_);

	while(temp->next!=NULL){
		if(max < temp->next->data){
			prev=temp;
			max=temp->next->data;
		}
		temp=temp->next;
	}
	if(max==(*queue_)->data){
		for_free=(*queue_);
		max=(*queue_)->data;
		(*queue_)=(*queue_)->next;
		free(for_free);
	}
	else{
 		for_free=prev->next;
		prev->next=prev->next->next;
		free(for_free);
	}
	return max;
}
int find_min_q(queue ** queue_){
	if((*queue_)==NULL){
		return 0;
	}
	int min=(*queue_)->data;
	queue *temp,*prev,*for_free;
	temp=(*queue_);

	while(temp->next!=NULL){
		if(min > temp->next->data){
			prev=temp;
			min=temp->next->data;
		}
		temp=temp->next;
	}
	if(min==(*queue_)->data){
		for_free=(*queue_);
		min=(*queue_)->data;
		(*queue_)=(*queue_)->next;
		free(for_free);
	}
	else{
 		for_free=prev->next;
		prev->next=prev->next->next;
		free(for_free);
	}
	return min;
}


void print_stack(stack * stack_){
	while(stack_!=NULL){
		printf("%d ",stack_->data);
		stack_=stack_->next;
	}
	printf("\n");
}
void print_queue(queue * queue_){
	while(queue_!=NULL){
		printf("%d ",queue_->data);
		queue_=queue_->next;
	}
	printf("\n");
}
void print_bst(bst *bst_){
	if(bst_==NULL){
		return;
	}
	print_bst(bst_->right);
	printf("%d ",bst_->data);
	if(bst_->left!=NULL){
		print_bst(bst_->left);
	}
}
void report(double t_stack,double t_queue,double t_bst,char name[SIZE_N]){
	printf("%s:\n",name);
	printf("%-14s%-9s%-9s%s\n","Structures","Stack","Queue","BST");
	printf("%-14s%-9.2lf%-9.2lf%.2lf\n","Exec. Time",t_stack*100000,t_queue*100000,t_bst*100000);
}