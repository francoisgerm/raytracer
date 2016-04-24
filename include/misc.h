#ifndef MISC_H
#define MISC_H

#include "geometry.h"
#include "entry.h"


typedef struct ssettings{
	int depth;
	double size_x, size_y, size_z; // scene's
	color back;
	source s;
	point obs;
	
	flist* facets;

	// screen
	point screenA;
	point screenB;
	double width_px, height_px; // IN PX
	double width_scn, height_scn; // IN SCENE UNITS
	point top_lefthand ; //point en haut a gauche de l'écran
  vector i,j ;


} settings;

double min3 (double a, double b, double c);
double min2 (double a, double b);
int inScene (settings s, point p);
#endif
