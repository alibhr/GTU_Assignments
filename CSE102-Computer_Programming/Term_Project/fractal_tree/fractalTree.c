#include <stdio.h>
#include <math.h>
#include "Point2D.h"

#define PI 3.141592

void fractalTree(Point2D **points,Point2D centerPoint,double lenght,double angle,double increaseAngle,int iterate);
void export_eps(Point2D *head,char *fileName);

int main(){

	Point2D *head = NULL;
	Point2D center = {0,0,NULL};

	fractalTree(&head,center,10,90,30,10);
	
	export_eps(head,"fractalTree.eps");
	
	printPoints(head);
	
	freePoints(&head);

	return 0;
}

void fractalTree(Point2D **points,Point2D centerPoint,double lenght,double angle,double increaseAngle,int iterate){
	if(iterate <= 0){
		add(points,centerPoint);
		return;
	}
	Point2D aPoint = {	centerPoint.x + lenght * cos(PI * angle / 180),
						centerPoint.y + lenght * sin(PI * angle / 180),NULL};

	add(points,centerPoint);
	fractalTree(points,aPoint,lenght*8/10,angle-increaseAngle,increaseAngle,iterate-1);

	add(points,centerPoint);

	fractalTree(points,aPoint,lenght*8/10,angle+increaseAngle,increaseAngle,iterate-1);
	add(points,centerPoint);
}


void export_eps(Point2D *head,char *fileName){

	FILE *filep = fopen(fileName,"w");
	fprintf(filep,"%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(filep,"%%%%BoundingBox %lf %lf %lf %lf\n",-50.0,-50.0,50.0,50.0);
	fprintf(filep,"%lf setlinewidth\n",0.10);
	fprintf(filep, "%lf %lf moveto\n",0.0,0.0);

	while(head != NULL){
		fprintf(filep,"%lf %lf lineto\n",head->x,head->y);
		head = head->next;
	}
	fprintf(filep,"stroke\n");
	fprintf(filep,"showpage\n");

	fclose(filep);
}