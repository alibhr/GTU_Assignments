#include <stdio.h>
#include "VectorGraphics.h"

double f(double x){ return sin(x); }
double fo(double x){ return 1; }
Tree* createTree(Tree *root);
void frakltals();

int main(){

	//function of y = sin(x)
	Figure *fig = start_figure(100.0,100.0);
	set_thickness_resolution(fig,0.1,0.1);
	draw_fx(fig,f,-200,200);

	//function of y = 1
	Figure *fig1 = start_figure(300.0,300.0);
	set_thickness_resolution(fig1,0.1,0.1);
	draw_fx(fig1,fo,-200,200);
	sprintf(fig1->text,"%s %d","Ali",10);
	fig1->textPoint.x=0;
	fig1->textPoint.y=-3;

	//ellipse
	Point2D center = {0,20,NULL};
	Figure *fig2 = start_figure(100.0,100.0);
	set_thickness_resolution(fig2,0.1,0.1);
	draw_ellipse(fig2,&center,30,15);
	
	//circle
	Figure *fig3 = start_figure(100.0,100.0);
	set_thickness_resolution(fig3,0.1,0.1);
	draw_circle(fig3,&center,5);

	//binary search tree
	Tree *root = NULL;
	root = createTree(root);
	Figure *fig4 = start_figure(400.0,400.0);
	set_thickness_resolution(fig4,0.1,0.1);
	Point2D centerTree = {0,140,NULL};
	draw_binary_tree(fig4,root,centerTree,findDepthOfTree(root));

	append_figures(fig,fig1);
	append_figures(fig,fig2);
	append_figures(fig,fig3);

	export_eps(fig,"out.eps");
	export_eps(fig4,"bst.eps");

	freeTree(&root);
	destroyFigure(&fig);
	destroyFigure(&fig4);

	frakltals();
	
	return 0;

}

void frakltals(){
	Point2D center = {0,0,NULL};

	Figure *fig = start_figure(100.0,100.0);
	set_thickness_resolution(fig,0.1,0.1);
	draw_fractal_circuit(fig,&center,50);
	export_eps(fig,"fractal.eps");
	destroyFigure(&fig);

	Figure *fig1 = start_figure(400.0,400.0);
	set_thickness_resolution(fig1,0.1,0.1);
	draw_fractal_circuit1(fig1,&center,100,8);
	export_eps(fig1,"fractal1.eps");
	destroyFigure(&fig1);

	Figure *fig2 = start_figure(300.0,75.0);
	set_thickness_resolution(fig2,0.1,0.1);
	draw_fractal_lines(fig2,-150,34,300);
	export_eps(fig2,"fractal2.eps");
	destroyFigure(&fig2);
	
	Figure *fig3 = start_figure(300.0,100.0);
	set_thickness_resolution(fig3,0.1,0.1);
	draw_fractalTree(fig3,center,10,90,30,10);
	export_eps(fig3,"fractal3.eps");
	destroyFigure(&fig3);

	//-----------------
	Figure *fig4 = start_figure(100.0,100.0);
	set_thickness_resolution(fig4,0.1,0.1);
	Figure *fig5 = start_figure(100.0,100.0);
	set_thickness_resolution(fig5,0.1,0.1);
	Figure *fig6 = start_figure(100.0,100.0);
	set_thickness_resolution(fig6,0.1,0.1);
	Figure *fig7 = start_figure(100.0,100.0);
	set_thickness_resolution(fig7,0.1,0.1);

	draw_fractalTree(fig4,center,10,  0,30,8);
	draw_fractalTree(fig5,center,10, 90,30,8);
	draw_fractalTree(fig6,center,10,180,30,8);
	draw_fractalTree(fig7,center,10,270,30,8);

	append_figures(fig4,fig5);
	append_figures(fig4,fig6);
	append_figures(fig4,fig7);

	export_eps(fig4,"fractal4.eps");
	
	destroyFigure(&fig4);
	//---------------

	Figure *fig9 = start_figure(300.0,100.0);
	set_thickness_resolution(fig9,0.1,0.1);
	draw_fractalTree_3(fig9,center,10,90,40,5);
	export_eps(fig9,"fractal6.eps");
	destroyFigure(&fig9);

	Figure *fig0 = start_figure(300.0,100.0);
	set_thickness_resolution(fig0,0.1,0.1);
	draw_fractal_aTree(fig0,center,10,90,20,40,11);
	export_eps(fig0,"fractal7.eps");
	destroyFigure(&fig0);
}

Tree* createTree(Tree *root){

	root=insertToTree(root,100);
	root=insertToTree(root,50);
	root=insertToTree(root,125);
	root=insertToTree(root,25);
	root=insertToTree(root,75);
	root=insertToTree(root,110);
	root=insertToTree(root,130);
	root=insertToTree(root,15);
	root=insertToTree(root,90);
	root=insertToTree(root,105);
	root=insertToTree(root,115);
	root=insertToTree(root,127);
	root=insertToTree(root,135);
	root=insertToTree(root,35);
	root=insertToTree(root,60);

	return root;
}
