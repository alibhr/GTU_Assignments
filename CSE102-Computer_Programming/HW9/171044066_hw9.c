#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 16
struct person{
	char name[SIZE];
	char surname[SIZE];
	char musical_work[SIZE];
	int age;
	struct person *next;
}*top;
void addNode(char name[],char surname[],char creation[],int age);
void print_stack();
void deleteNode();
void Sort_Increasingly();
struct person * create_sorted_stack(struct person *ordered,char name[],char surname[],char creation[],int age);
struct person * create_sorted_stack_(struct person *ordered,char name[],char surname[],char creation[],int age);
void Sort_Alphabetically();
int compare(char str1[],char str2[]);
int main(){
	struct person *temp;
	top=NULL;
	int selection,flag=1,age;
	char name[SIZE],surname[SIZE],musical_work[SIZE];
	while(flag){
		printf("\t\t*****MENU*****\n");
		printf("   1-\tAdd a person to the stack\n");
		printf("   2-\tPop a person from the stack\n");
		printf("   3-\tSort Alphabetical Order\n");
		printf("   4-\tSort age in increasing order\n");
		printf("   5-\tExit menu\n");
		printf("   6-\tShow current stack\n");
		printf("   ");
		scanf("%d",&selection);
		switch(selection){
			case 1:
				printf("Name:");
				scanf(" %[^\n]s",name);
				printf("Surname:");
				scanf(" %[^\n]s",surname);
				printf("creation:");
				scanf(" %[^\n]s",musical_work);
				printf("age:");
				scanf("%d",&age);
				addNode(name,surname,musical_work,age);
				print_stack(top);
			break;
			case 2:
				deleteNode();
				print_stack(top);
			break;
			case 3:
				Sort_Alphabetically();
				print_stack(top);
			break;
			case 4:
				Sort_Increasingly();
				print_stack(top);
			break;
			case 5:
				flag=0;
			break;
			case 6:
				print_stack(top);
			break;
			default:
				printf("invalid selection,try again!\n");
			break;
		}
	}
	while(top!=NULL){
		temp=top;
		top=top->next;
		free(temp);
	}
	return 0;
}
void addNode(char name[],char surname[],char creation[],int age){
	struct person *temp;
	if(top==NULL){
		top=(struct person*)malloc(sizeof(struct person));
		strcpy(top->name,name);
		strcpy(top->surname,surname);
		strcpy(top->musical_work,creation);
		top->age=age;
		top->next=NULL;
	}
	else{
		temp=(struct person*)malloc(sizeof(struct person));
		strcpy(temp->name,name);
		strcpy(temp->surname,surname);
		strcpy(temp->musical_work,creation);
		temp->age=age;
		temp->next=top;
		top=temp;
	}
}
void print_stack(){
	struct person *temp;
	temp=top;
	int i=1;
	printf("%-18s%-16s%-16s%-16s\n","  Name","Surname","musical_work","age");
	for(i=1;temp!=NULL;i++){
		printf("%d-",i);
		printf("%-16s",temp->name);
		printf("%-16s",temp->surname);
		printf("%-16s",temp->musical_work);
		printf("%-16d",temp->age);
		printf("\n");
		temp=temp->next;	
	}
	printf("\n");
}
void deleteNode(){
	if(top!=NULL){
		struct person *temp;
		temp=top;
		top=top->next;
		free(temp);
	}
}
void Sort_Increasingly(){
	struct person *ordered;
	struct person *temp;
	ordered=NULL;
	temp=top;
	while(temp!=NULL){
		ordered=create_sorted_stack(ordered,temp->name,temp->surname,temp->musical_work,temp->age);
		temp=temp->next;
	}
	top=ordered;
}
struct person * create_sorted_stack(struct person *ordered,char name[],char surname[],char creation[],int age){
	if(ordered==NULL){
		ordered=(struct person*)malloc(sizeof(struct person));
		strcpy(ordered->name,name);
		strcpy(ordered->surname,surname);
		strcpy(ordered->musical_work,creation);
		ordered->next=NULL;
		ordered->age=age;
		return ordered;
	}
	if(age < ordered->age){
		struct person *new=(struct person*)malloc(sizeof(struct person));
		strcpy(new->name,name);
		strcpy(new->surname,surname);
		strcpy(new->musical_work,creation);
		new->age=age;
		new->next=ordered;
		return new;
	}
	if(age >= ordered->age){
		struct person *temp=ordered;
		while(temp->next!= NULL && age > temp->next->age){
			temp=temp->next;
		}
		struct person *new=(struct person*)malloc(sizeof(struct person));
		strcpy(new->name,name);
		strcpy(new->surname,surname);
		strcpy(new->musical_work,creation);
		new->age=age;
		new->next=temp->next;
		temp->next=new;
		return ordered;
	}
}
void Sort_Alphabetically(){
	struct person *ordered;
	struct person *temp;
	ordered=NULL;
	temp=top;
	while(temp!=NULL){
		ordered=create_sorted_stack_(ordered,temp->name,temp->surname,temp->musical_work,temp->age);
		temp=temp->next;
	}
	top=ordered;
}
struct person * create_sorted_stack_(struct person *ordered,char name[],char surname[],char creation[],int age){
	if(ordered==NULL){
		ordered=(struct person*)malloc(sizeof(struct person));
		strcpy(ordered->name,name);
		strcpy(ordered->surname,surname);
		strcpy(ordered->musical_work,creation);
		ordered->next=NULL;
		ordered->age=age;
		return ordered;
	}
	if(compare(name,ordered->name)<0){
		struct person *new=(struct person*)malloc(sizeof(struct person));
		strcpy(new->name,name);
		strcpy(new->surname,surname);
		strcpy(new->musical_work,creation);
		new->age=age;
		new->next=ordered;
		return new;
	}
	if(compare(name,ordered->name)>=0){
		struct person *temp=ordered;
		while(temp->next!= NULL && compare(name,temp->next->name)>0){
			temp=temp->next;
		}
		struct person *new=(struct person*)malloc(sizeof(struct person));
		strcpy(new->name,name);
		strcpy(new->surname,surname);
		strcpy(new->musical_work,creation);
		new->age=age;
		new->next=temp->next;
		temp->next=new;
		return ordered;
	}
}
int compare(char str1[],char str2[]){
	int i=0;
	while(str1[i]!='\0' && str2[i]!='\0' && str1[i]==str2[i]){
		i++;
	}
	return (int)(str1[i]-str2[i]);
}