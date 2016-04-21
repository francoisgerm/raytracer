#ifndef MISC_H
#define MISC_H

#include "geometry.h"
#include "entry.h"

typedef struct ssettings {
	int depth;
	double size_x, size_y, size_z;
	color back;
} settings;

typedef struct sscreen {
    point screenA;
    point screenB;
    point obs;
    double width, height ;
    point top_lefthand ; //point en haut a gauche de l'écran
    vector i,j ;
} screen ;

double min3 (double a, double b, double c);
double min2 (double a, double b);
int inScene (settings s, point p);
#endif
