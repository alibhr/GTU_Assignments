#ifndef _POINT2D_H_
#define _POINT2D_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Point2D{
	double x;
	double y;
	struct Point2D *next;
}Point2D;

void add(Point2D **head,Point2D data);
void freePoints(Point2D **head);
void printPoints(Point2D *head);

#endif