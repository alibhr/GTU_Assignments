#include "Point2D.h"

void add(Point2D **head,Point2D data){
	if((*head) == NULL){
		(*head)=(Point2D*)malloc(sizeof(Point2D));
		(*head)->x = data.x;
		(*head)->y = data.y;
		(*head)->next = NULL;
		return;
	}

	Point2D *temp = (*head);

	while(temp->next){
		temp = temp->next;
	}

	temp->next = (Point2D*)malloc(sizeof(Point2D*));
	temp->next->x = data.x;
	temp->next->y = data.y;
	temp->next->next = NULL;

}

void printPoints(Point2D *head){
	Point2D *temp = head;

	while(temp){
		printf("x:%lf    y:%lf\n",temp->x,temp->y);
		temp = temp->next;
	}
	free(temp);
}

void freePoints(Point2D **head){
	if(head == NULL)
		return;
	
	while((*head)){
		Point2D *temp = (*head);
		(*head)=(*head)->next;
		free(temp);
	}
}