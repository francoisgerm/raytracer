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
                printf("lolilol");
        }
        point intersection;
        intersection.x = 0;
        intersection.y = 0;
        intersection.z = 0;

        // r = ray vector ; p(r) = point ; a in f ; u & v vectors of f
        // solve : p(r) + t.r = a + alpha*u + beta*v

        vector u = ptsToVect(f.a,f.b);
        vector v = ptsToVect(f.a,f.c);
        vector n = crossProduct(u,v);

        double t, alpha, beta;
        t = - dotProduct(n, ptsToVect(f.a, incident_r.o)) / dotProduct(n, incident_r.v);

        alpha = dotProduct(crossProduct(ptsToVect(f.a, incident_r.o), v), incident_r.v) / dotProduct(n, incident_r.v);
        beta = dotProduct(crossProduct(u, ptsToVect(f.a, incident_r.o)), incident_r.v) / dotProduct(n, incident_r.v);

    printf ("\n ---------- \nt = %f\nalpha = %f\nbeta=%f\n----------\n", t, alpha, beta);

        printf ("normale :      %f %f %f \n", f.n.x, f.n.y, f.n.z);
        printf ("rayon :        %f %f %f \n", incident_r.v.x, incident_r.v.y, incident_r.v.z);
        printf ("u :            %f %f %f \n", u.x, u.y, u.z);
        printf ("v :            %f %f %f \n", v.x, v.y, v.z);

        printf ("%f %f %f \n", ptsToVect(f.a, incident_r.o).x, ptsToVect(f.a, incident_r.o).y, ptsToVect(f.a, incident_r.o).z);
        printf ("%f\n ", dotProduct(f.n, ptsToVect(f.a, incident_r.o)) );

        if (t >=0 && 0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1) {
            
                intersection = vSum(incident_r.o, eDot(t, incident_r.v));
        } else {
         //       printf ("No intersection point. Returning origin");
        }
                intersection = vSum(incident_r.o, eDot(t, incident_r.v));
        

        point intersection_bis = vSum(f.a, vSum(eDot(alpha, u), eDot(beta, v)));
        printf ("\nintersection : %f %f %f \n", intersection_bis.x, intersection_bis.y, intersection_bis.z);

        return intersection;

}
