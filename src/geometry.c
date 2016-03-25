#include "../include/includes.h"


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
        return vSum(b, eDot(-1, a));
}

int isInFacet (point a, facet f) {
        printf ("your turn, Gaël !");
        return 0;
}
