void export_eps(Figure *fig, char *file_name){
	Figure *iter_fig = fig;
	Point2D *iter_point;
	FILE *fp;

	fp = fopen(file_name,"w");
	fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(fp,"%%%%BoundingBox %lf %lf %lf %lf\n",-(fig->width)/2.0,-(fig->height)/2.0,(fig->width)/2.0,(fig->height)/2.0);

	while(iter_fig != NULL)
	{
		if(iter_fig->point != NULL)
		{
			iter_point = iter_fig->point;
			fprintf(fp,"%lf setlinewidth\n",iter_fig->thickness);
			fprintf(fp,"%lf %lf %lf setrgbcolor\n",iter_fig->c.R,iter_fig->c.G,iter_fig->c.B);
			if(iter_fig->text.flag != 0)
			{
				fprintf(fp,"/Times-Roman findfont 2 scalefont setfont\n");
				fprintf(fp,"%lf %lf moveto\n",iter_fig->text.x,iter_fig->text.y);
				fprintf(fp,"(%d) show\n",iter_fig->text.num);
			}
			if(iter_point != NULL)
			{
				fprintf(fp,"%lf %lf moveto\n",iter_point->x,iter_point->y);
				for(;iter_point != NULL ; iter_point = iter_point->next)
				{
					if(iter_point->jump == 0)
						fprintf(fp,"%lf %lf lineto\n",iter_point->x,iter_point->y);
					else
						fprintf(fp,"%lf %lf moveto\n",iter_point->x,iter_point->y);	
				}
			}
			fprintf(fp,"stroke\n");
		}
		iter_fig = iter_fig->next_figure;
	}
	fclose(fp);
	free_fig(fig);	// Figure free
}