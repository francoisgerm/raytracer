#include "misc.h"

double min3 (double a, double b, double c) {
	if (a <= b) {
		if (a <= c)
			return a;
		else
			return c;
	} else {
		if (b <= c)
			return b;
		else
			return c;
	}

}

int inScene (settings s, point p) {
	if (p.x > s.size_x || p.y > s.size_y || p.z > s.size_z || p.x < -10e-7 || p.y <	-10e-7
	|| p.z < -10e-7)
		return 0;
	else
		return 1;
}

double min2 (double a, double b) {
	return a < b ? a : b;
}
