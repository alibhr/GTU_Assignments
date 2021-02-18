#include "VectorGraphics.h"

Figure* getLine(Figure *fig, Point2D begin, Point2D end);

void pushPoint2D(Point2D **head , Point2D aPoint){
	if((*head)==NULL){
		(*head) = (Point2D*)malloc(sizeof(Point2D));
		(*head)->x = aPoint.x;
		(*head)->y = aPoint.y;
		(*head)->next = NULL;
		return;
	}

	Point2D *new = (Point2D*)malloc(sizeof(Point2D));
	new->x = aPoint.x;
	new->y = aPoint.y;
	new->next = (*head);
	(*head) = new ;
}

void pushFigure(Figure **head , Figure *aFigure){
	if(aFigure == NULL)
		return;

	if((*head)==NULL){
		(*head) = aFigure;
		(*head)->next = NULL;
		return;
	}
	aFigure->next = (*head);
	(*head) = aFigure;
}

void append_figures(Figure *fig1, Figure *fig2){
	Figure *temp = fig1;

	if(temp == NULL){
		printf("ERROR : fig_NULL\n");
		exit(1);
	}

	while(temp->next != NULL){
		temp = temp->next;
	}

	temp->next = fig2;
}

Figure* start_figure(double width, double height){
	Figure *newFigure = (Figure*)malloc(sizeof(Figure));

	newFigure->width = width;
	newFigure->height = height;

	newFigure->next = NULL;
	newFigure->points = NULL;

	newFigure->text = (char*)malloc(sizeof(char)*SIZE);
	newFigure->text[0] = '\0';

	return newFigure;
}

void set_thickness_resolution(Figure *fig, double thickness, double resolution){
	fig->thickness=thickness;
	fig->resolution=resolution;
}

void set_color(Figure *fig, Color c){
	fig->color = c;
}

void draw_fx(Figure *fig, double f(double x), double start_x, double end_x){

	Point2D newPoint;

	if(fig == NULL){
		printf("ERROR : fig_Null.\n");
		exit(1);
	}

	if(end_x < start_x){
		double temp = end_x;
		end_x = start_x;
		start_x = temp;
	}

	for(double i=start_x ; i<end_x ; i+=fig->resolution){
		start_point(&newPoint,i,f(i));
		pushPoint2D(&(fig->points),newPoint);
	}
}

void start_point(Point2D *aPoint,double x, double y){
	if(aPoint == NULL){
		printf("ERROR : null_Point\n");
		return ;
	}

	aPoint->x = x;
	aPoint->y = y;
	aPoint->next = NULL;
}

void draw_polyline(Figure *fig, Point2D *poly_line, int n){
	for(int i=0 ; i<n ; ++i){
		pushPoint2D(&(fig->points),poly_line[i]);
	}
}

void draw_circle(Figure *fig,Point2D *center, double r){
	draw_ellipse(fig,center,r,r);
}

void draw_ellipse(Figure *fig ,Point2D *center, double a, double b){

	Point2D newPoint;

	for(double i = -a ; i < a ;i+=fig->resolution){
		start_point(&newPoint,
					i,
					sqrt((1-((i*i)/(a*a)))*b*b)
		);
		pushPoint2D(&(fig->points),newPoint);
	}

	for(double i = a ; i > -a ;i-=fig->resolution){
		start_point(&newPoint,
					i,
					-sqrt((1-((i*i)/(a*a)))*b*b)
		);
		pushPoint2D(&(fig->points),newPoint);
	}
	start_point(&newPoint,
				-a,
				-sqrt((1-((a*a)/(a*a)))*b*b)
	);
	pushPoint2D(&(fig->points),newPoint);


	if(center == NULL)
		return;

	Point2D *temp = fig->points;
	while(temp != NULL){
		temp->x += center->x;
		temp->y += center->y;
		temp = temp->next;
	}
}

// !!!!!! scale problem
void draw_binary_tree(Figure *fig, Tree *root, Point2D center,int depth){

	if(root == NULL)
		return;
	
	Figure *circle = start_figure(fig->width,fig->height);
	set_thickness_resolution(circle,fig->thickness,fig->resolution);
	draw_circle(circle,&center,BINARY_TREE_RADIUS);
	
	sprintf(circle->text,"%d",root->data);
	circle->textPoint.x=center.x - SCALE_FONT/2;
	circle->textPoint.y=center.y;
	
	append_figures(fig,circle);

	if(root->left != NULL){
		Point2D line = {center.x - BINARY_TREE_RADIUS * cos(PI * BINARY_TREE_ANGLE / 180),
						center.y - BINARY_TREE_RADIUS * sin(PI * BINARY_TREE_ANGLE / 180),
						NULL
		};

		Figure *figConnection=start_figure(fig->width,fig->height);
		set_thickness_resolution(figConnection,fig->thickness,fig->resolution);
		pushPoint2D(&(figConnection->points),line);
		line.x -= BINARY_TREE_RADIUS * pow(2,depth);
		line.y -= BINARY_TREE_RADIUS * pow(2,depth);
		pushPoint2D(&(figConnection->points),line);
		line.y -= BINARY_TREE_RADIUS;
		
		append_figures(fig,figConnection);

		draw_binary_tree(fig, root->left, line, depth-1);
	}

	if(root->right != NULL){
		Point2D line = {center.x + BINARY_TREE_RADIUS * cos(PI * BINARY_TREE_ANGLE / 180),
						center.y - BINARY_TREE_RADIUS * sin(PI * BINARY_TREE_ANGLE / 180),
						NULL
		};

		Figure *figConnection=start_figure(fig->width,fig->height);
		set_thickness_resolution(figConnection,fig->thickness,fig->resolution);
		pushPoint2D(&(figConnection->points),line);
		line.x += BINARY_TREE_RADIUS * pow(2,depth);
		line.y -= BINARY_TREE_RADIUS * pow(2,depth);
		pushPoint2D(&(figConnection->points),line);
		line.y -= BINARY_TREE_RADIUS;
		
		append_figures(fig,figConnection);

		draw_binary_tree(fig, root->right, line, depth-1);
	}
}

void draw_fractal_circuit(Figure *fig, Point2D *center, int num_iterations){
	if(num_iterations < 1){
		return;
	}
	Figure *circle = start_figure(fig->width,fig->height);
	set_thickness_resolution(circle,fig->thickness,fig->resolution);
	draw_circle(circle,center,num_iterations);
	append_figures(fig,circle);
	draw_fractal_circuit(fig,center,num_iterations-1);
}

void draw_fractal_circuit1(Figure *fig, Point2D *center, int r, int num_iterations){
	if(num_iterations < 1 || r < 1){
		return;
	}
	
	Figure *circle = start_figure(fig->width,fig->height);
	set_thickness_resolution(circle,fig->thickness,fig->resolution);
	draw_circle(circle,center,r);
	append_figures(fig,circle);
	
	Point2D newCenter1 = {center->x-r,center->y,NULL};
	draw_fractal_circuit1(fig,&newCenter1,ceil(r/2),num_iterations-1);
	
	Point2D newCenter2 = {center->x+r,center->y,NULL};
	draw_fractal_circuit1(fig,&newCenter2,ceil(r/2),num_iterations-1);

	Point2D newCenter3 = {center->x,center->y+r,NULL};
	draw_fractal_circuit1(fig,&newCenter3,ceil(r/2),num_iterations-1);

	Point2D newCenter4 = {center->x,center->y-r,NULL};
	draw_fractal_circuit1(fig,&newCenter4,ceil(r/2),num_iterations-1);
}

void draw_fractal_lines(Figure *fig, int x,int y, int len){
	if(len < 1){
		return;
	}

	Point2D begin = {x, y, NULL};
	Point2D end = {x + len, y, NULL};
	
	Figure *aLine =  start_figure(fig->width,fig->height);
	set_thickness_resolution(aLine,fig->thickness,fig->resolution);
	pushPoint2D(&(aLine->points),begin);
	pushPoint2D(&(aLine->points),end);
	append_figures(fig,aLine);

	draw_fractal_lines(fig,x,y-10,len/3);
	draw_fractal_lines(fig,x + 2*len/3,y-10,len/3);
}

void draw_fractalTree(Figure *fig,Point2D centerPoint,double lenght,double angle,double increaseAngle,int iterate){
	if(iterate <= 0){
		pushPoint2D(&(fig->points),centerPoint);
		return;
	}
	Point2D aPoint = {	centerPoint.x + lenght * cos(PI * angle / 180),
						centerPoint.y + lenght * sin(PI * angle / 180),NULL};

	pushPoint2D(&(fig->points),centerPoint);
	draw_fractalTree(fig,aPoint,lenght*8/10,angle-increaseAngle,increaseAngle,iterate-1);

	draw_fractalTree(fig,aPoint,lenght*8/10,angle+increaseAngle,increaseAngle,iterate-1);
	pushPoint2D(&(fig->points),centerPoint);
}

void draw_fractal_aTree(Figure *fig,Point2D centerPoint,double lenght,double angle,double d1,double d2,int iterate){
	if(iterate <= 0){
		pushPoint2D(&(fig->points),centerPoint);
		return;
	}
	Point2D aPoint = {	centerPoint.x + lenght * cos(PI * angle / 180),
						centerPoint.y + lenght * sin(PI * angle / 180),NULL};

	pushPoint2D(&(fig->points),centerPoint);
	draw_fractal_aTree(fig,aPoint,lenght*8/10,angle-d2,d1,d2,iterate-1);

	draw_fractal_aTree(fig,aPoint,lenght*8/10,angle+d1,d1,d2,iterate-1);
	pushPoint2D(&(fig->points),centerPoint);
}

void draw_fractalTree_3(Figure *fig,Point2D centerPoint,double lenght,double angle,double increaseAngle,int iterate){
	if(iterate <= 0){
		pushPoint2D(&(fig->points),centerPoint);
		return;
	}
	Point2D aPoint = {	centerPoint.x + lenght * cos(PI * angle / 180),
						centerPoint.y + lenght * sin(PI * angle / 180),NULL};

	pushPoint2D(&(fig->points),centerPoint);
	draw_fractalTree_3(fig,aPoint,lenght*8/10,angle-increaseAngle,increaseAngle,iterate-1);

	pushPoint2D(&(fig->points),centerPoint);
	draw_fractalTree_3(fig,aPoint,lenght*8/10,angle,increaseAngle,iterate-1);

	draw_fractalTree_3(fig,aPoint,lenght*8/10,angle+increaseAngle,increaseAngle,iterate-1);
	pushPoint2D(&(fig->points),centerPoint);
}

/*
void draw_koch_snowflake(Figure *fig, Point2D *center, int size, int num_iterations){
	if(num_iterations < 1){
		return;
	}

	draw_koch_snowflake(fig,center,size/3,num_iterations-1);

	Point2D begin = {center->x, center->y, NULL};
	Point2D end = {center->x + size/3, center->y, NULL};
	append_figures(fig,getLine(fig, begin, end));

	begin.x = center->x + size/3;
	end.x = begin.x + size/3 * sin(30*PI/180);
	end.y = begin.y + size/3 * sin(60*PI/180);
	append_figures(fig,getLine(fig, begin, end));

	begin.x = end.x;
	begin.y = end.y;
	end.x = begin.x + size/3 * sin(30*PI/180);
	end.y = begin.y - size/3 * sin(60*PI/180);
	append_figures(fig,getLine(fig, begin, end));

	begin.x = end.x;
	begin.y = end.y;
	end.x = center->x + size;
	append_figures(fig,getLine(fig, begin, end));
}
*/

Figure* getLine(Figure *fig, Point2D begin, Point2D end){
	Figure *aLine =  start_figure(fig->width,fig->height);
	set_thickness_resolution(aLine,fig->thickness,fig->resolution);
	pushPoint2D(&(aLine->points),begin);
	pushPoint2D(&(aLine->points),end);
	return aLine;
}

void export_eps(Figure *fig, char *file_name){
	
	Figure *tempFig = fig;
	Point2D *tempPoint = NULL;

	FILE *filep = fopen(file_name,"w");

	fprintf(filep,"%%!PS-Adobe-3.0 EPSF-3.0\n");

	fprintf(filep,"%%%%BoundingBox %lf %lf %lf %lf\n",  
			(fig->width/-2.0),
			(fig->height/-2.0),
			(fig->width/2.0),
			(fig->height/2.0)
	);
	while(fig != NULL){
		fprintf(filep,"%lf setlinewidth\n",fig->thickness);
		

		if( fig->text[0] != '\0'){
			fprintf(filep,"%s %d %s","/Times-Roman findfont", SCALE_FONT ,"scalefont setfont\n");
			fprintf(filep,"%lf %lf moveto\n",fig->textPoint.x,fig->textPoint.y);
			fprintf(filep,"(%s) show\n",fig->text);
		}

		if(fig->points != NULL)
			fprintf(filep, "%lf %lf moveto\n",fig->points->x,fig->points->y);

		tempPoint = fig->points;
		while(fig->points != NULL){
			fprintf(filep,"%lf %lf lineto\n",fig->points->x,fig->points->y);
			fig->points = fig->points->next;
		}
		fprintf(filep,"stroke\n");

		fig->points = tempPoint;
		fig = fig->next;
	}

	fprintf(filep,"showpage\n");

	fig = tempFig;
	fclose(filep);
}

Tree* insertToTree(Tree *root, int data){
	if(root==NULL){
		root=(Tree*)malloc(sizeof(Tree));
		root->data=data;
		root->right=NULL;
		root->left=NULL;
		return root;
	}
	if(data > root->data){
		root->right=insertToTree(root->right,data);
		return root;
	}
	else if(data < root->data){
		root->left=insertToTree(root->left,data);
		return root;
	}
	else{
		printf("element couldn't be added (%d has been already exist in tree)\n",root->data);
		return root;
	}
}

void printTree(Tree *root){
	if(root==NULL){
		return;
	}
	printTree(root->left);
	printf("%d\n",root->data);
	printTree(root->right);
}

int findDepthOfTree(Tree *root){
	if(root == NULL){
		return 0;
	}

	int r = 1 + findDepthOfTree(root->right);
	int l = 1 + findDepthOfTree(root->left);

	if(r > l)
		return r;
	else
		return l;
}

int _findDepthOfTree(Tree *root){
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

void _strcpy(char *s1,char *s2){
	while((*(s1++) = *(s2++)));
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

void destroyPoint2D(Point2D **head){
	Point2D *temp=NULL;

	while((*head) != NULL){
		temp = (*head);
		(*head) = (*head)->next;
		free(temp);
	}
}

void destroyFigure(Figure **head){
	Figure *temp=NULL;

	while((*head) != NULL){
		temp = (*head);
		(*head) = (*head)->next;
		destroyPoint2D( &(temp->points) );
		free(temp);
	}
}
