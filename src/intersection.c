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
        // solve : p(r) + t.r = a + alpha*u + beta*v

        vector u = ptsToVect(f.a,f.b);
        vector v = ptsToVect(f.a,f.c);
        vector n = crossProduct(u,v);

        double t, alpha, beta;
        t = - dotProduct(n, ptsToVect(f.a, incident_r.o)) / dotProduct(n, incident_r.v);

        point intersection = vSum(incident_r.o, eDot(t, incident_r.v));

        if (isInFacet (intersection, f))
            return intersection;
        else {
            printf ("Ray doesn't intersect the facet, returning origin");

            intersection.x = 0;
            intersection.y = 0;
            intersection.z = 0;

            return intersection;
        }
 /*       alpha = dotProduct(crossProduct(ptsToVect(f.a, incident_r.o), v), incident_r.v) / dotProduct(n, incident_r.v);
        beta = dotProduct(crossProduct(u, ptsToVect(f.a, incident_r.o)), incident_r.v) / dotProduct(n, incident_r.v);

        printf ("\n ---------- \nt = %f\nalpha = %f\nbeta=%f\n----------\n", t, alpha, beta);

        printf ("normale :      %f %f %f \n", f.n.x, f.n.y, f.n.z);
        printf ("rayon :        %f %f %f \n", incident_r.v.x, incident_r.v.y, incident_r.v.z);
        printf ("u :            %f %f %f \n", u.x, u.y, u.z);
        printf ("v :            %f %f %f \n", v.x, v.y, v.z);

        printf ("%f %f %f \n", ptsToVect(f.a, incident_r.o).x, ptsToVect(f.a, incident_r.o).y, ptsToVect(f.a, incident_r.o).z);
        printf ("%f\n ", dotProduct(f.n, ptsToVect(f.a, incident_r.o)) );*/
/*
        if (t >=0 && 0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1) {
            
                intersection = vSum(incident_r.o, eDot(t, incident_r.v));
        } else {
         //       printf ("No intersection point. Returning origin");
        }
    */            
        

  //      point intersection_bis = vSum(f.a, vSum(eDot(alpha, u), eDot(beta, v)));
//        printf ("\nintersection : %f %f %f \n", intersection_bis.x, intersection_bis.y, intersection_bis.z);

        return intersection;

}


int isInFacet (point a, facet f) {
        // first of we check that a is in the extended plane
        point b = ptsToVect (f.a, a);
        double prod = dotProduct (f.n, b);
        prod = 0.0;

        if ( prod == 0.0) { // a = alpha * f.u + beta * f.v
            vector u = ptsToVect (f.a, f.b);
            vector v = ptsToVect (f.a, f.c);

            double beta = (dotProduct (a, v) - dotProduct (v, u)/dotProduct(u,u) * dotProduct(a, u)) / (dotProduct(v,v) - dotProduct(u,v)*dotProduct(u,v)/dotProduct(u,u));
            double alpha = (dotProduct (a,u) - beta * dotProduct(u,v))/ dotProduct(u,u);

            printf ("alpha : %f\nbeta : %f\n", alpha, beta);
            if (0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1 && alpha + beta <= 1)
                return 1;
        } else {
            printf ("dotPro : %f\n", dotProduct(f.n, b));
        }

        return 0;
}