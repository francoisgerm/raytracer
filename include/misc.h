#ifndef MISC_H
#define MISC_H

#include "geometry.h"

typedef struct ssettings {
	int depth;
	double size_x, size_y, size_z;
} settings;

double min3 (double a, double b, double c);
double min2 (double a, double b);
int inScene (settings s, point p);
#endif
