#include "../include/includes.h"

facet createFacet (point a, point b, point c) {
        facet new_facet;
        new_facet.a = a;
        new_facet.b = b;
        new_facet.c = c;


        new_facet.n = normalize (crossProduct(ptsToVect(a,b), ptsToVect(a,c)));

        return new_facet;
}


point computeIntersection (ray incident_r, facet f){

        if (dotProduct(incident_r.v, f.n) == 0) {
            printf ("Ray doesn't intersect the facet, returning origin");

            point intersection;
            intersection.x = 0;
            intersection.y = 0;
            intersection.z = 0;

            return intersection;
        }

        // r = ray vector ; p(r) = point ; a in f ; u & v vectors of f
        // solve : p(r) + t.r = a + alpha*u + beta*v in t

        vector u = ptsToVect(f.a,f.b);
        vector v = ptsToVect(f.a,f.c);
        vector n = crossProduct(u,v);

        double t, alpha, beta;
        t = - dotProduct(n, ptsToVect(f.a, incident_r.o)) / dotProduct(n, incident_r.v);

        point intersection = vSum(incident_r.o, eDot(t, incident_r.v));

        return intersection;

}


int isInFacet (point a, facet f) {
        // first of we check that a is in the extended plane
        point b = ptsToVect (f.a, a);
        double prod = dotProduct (f.n, b);

        if ( fabs(prod) < 10e-7) { // a = alpha * f.u + beta * f.v
            vector u = ptsToVect (f.a, f.b);
            vector v = ptsToVect (f.a, f.c);


            double beta = (dotProduct (b, v) - (dotProduct (v, u)/dotProduct(u,u)) * dotProduct(b, u)) / (dotProduct(v,v) - dotProduct(u,v)*dotProduct(u,v)/dotProduct(u,u));
            double alpha = (dotProduct (b,u) - beta * dotProduct(u,v))/ dotProduct(u,u);


            if (0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && alpha + beta <= 1)
                return 1;
        }

        return 0;
}
