#ifndef VECTORGRAPHICS_H
#define VECTORGRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 16
#define PI  3.14159
#define SCALE_FONT 3
#define BINARY_TREE_RADIUS 5
#define BINARY_TREE_ANGLE 45

typedef struct Point2D{
	double x,y;
	struct Point2D *next;
}Point2D;

typedef struct Color{
	double R,G,B;
}Color;

typedef struct Figure{
	double width,height;
	double thickness,resolution;
	Color color;
	Point2D *points;
	char *text;
	Point2D textPoint;
	struct Figure *next;
}Figure;

typedef struct Tree{
	int data;
	struct Tree *right;
	struct Tree *left;
}Tree;


void pushPoint2D(Point2D **head, Point2D aPoint);
void pushFigure(Figure **head, Figure *aFigure);
void append_figures(Figure *fig1, Figure *fig2);

Figure* start_figure(double width, double height);
void set_thickness_resolution(Figure *fig, double thickness, double resolution);
void set_color(Figure *fig, Color c);
void draw_fx(Figure *fig, double f(double x), double start_x, double end_x);
void export_eps(Figure *fig, char *file_name);
void start_point(Point2D *aPoint,double x, double y);
void draw_polyline(Figure *fig, Point2D *poly_line, int n);
void draw_circle(Figure *fig,Point2D *center, double r);
void draw_ellipse(Figure *fig,Point2D *center,double a,double b);
void draw_binary_tree(Figure *fig, Tree *root, Point2D center, int depth);
void draw_fractal_circuit(Figure *fig, Point2D *center, int num_iterations);
void draw_fractal_circuit1(Figure *fig, Point2D *center, int r, int num_iterations);
void draw_fractal_lines(Figure *fig, int x,int y, int len);
void draw_fractalTree(Figure *fig,Point2D centerPoint,double lenght,double angle,double increaseAngle,int iterate);
void draw_fractal_aTree(Figure *fig,Point2D centerPoint,double lenght,double angle,double d1,double d2,int iterate);
void draw_fractalTree_3(Figure *fig,Point2D centerPoint,double lenght,double angle,double increaseAngle,int iterate);
//void draw_koch_snowflake(Figure *fig, Point2D *center, int size, int num_iterations);

Tree* insertToTree(Tree *root,int data);
void printTree(Tree *root);
int findDepthOfTree(Tree *root);
int _findDepthOfTree(Tree *root);
void freeTree(Tree **root);

void destroyPoint2D(Point2D **head);
void destroyFigure(Figure **head);

void _strcpy(char *s1,char *s2);

#endif
