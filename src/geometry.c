#include "geometry.h"
#include "intersection.h"

#include <stdio.h>


vector crossProduct (vector a, vector b) {
        vector result;

        result.x = a.y * b.z - a.z * b.y;
        result.y = a.z * b.x - a.x * b.z;
        result.z = a.x * b.y - a.y * b.x;

        return result;
}

double dotProduct (vector a, vector b) {
        return (a.x*b.x + a.y*b.y + a.z*b.z);
}

vector normalize (vector v) {
        double norm = sqrt((v.x)*(v.x) + (v.y)*(v.y) + (v.z)*(v.z));
        v.x /= norm;
        v.y /= norm;
        v.z /= norm;

        return v;
}

vector eDot (double k, vector u) {
        u.x *= k;
        u.y *= k;
        u.z *= k;

        return u;
}

vector vSum (vector u, vector v) {
        v.x += u.x;
        v.y += u.y;
        v.z += u.z;

        return v;
}

vector ptsToVect (point a, point b) {
        return vSum(b, eDot(-1.0, a));
}

void printfPoint (char* name, point a) {
        printf ("%s | x : %f ; y : %f ; z : %f\n",name,  a.x, a.y, a.z);
}

float norma (vector v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}


int sameSide (facet f, point a, point b) {
	vector direction = ptsToVect (a, b);

	ray ab; 
	ab.v = direction;
	ab.o = a;

	if (fabs(dotProduct (direction, f.n)) > 10e-7) {
		point intersection = computeIntersection(ab, f);

		// intersection = t*ab + a
		point i_minus_a = vSum (intersection, eDot (-1.0, a));
		float t = 0.0;
	
		if (fabs (ab.v.x) > 10e-7)
			t = i_minus_a.x / ab.v.x;
		else if (fabs (ab.v.y) > 10e-7)
			t = i_minus_a.y / ab.v.y;
		else if (fabs (ab.v.z) > 10e-7)
			t = i_minus_a.z / ab.v.z;

		if (10e-7 < t && t < 1) 
			return 0;
		else
			return 1;
	} else {
		return 1;
	}
}
