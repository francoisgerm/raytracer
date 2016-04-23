/*#include "../include/includes.h"

int main (void) {
/*
        printf ("lolilol");

        point a;
        point b;
        point c;

        a.x = 1;
        a.y = 0;
        a.z = 0;

        b.x = 0;
        b.y = 1;
        b.z = 0;

        c.x = 0;
        c.y = 0;
        c.z = 1;

        facet lol = createFacet (a, b, c);

        printf("x = %f\ny = %f\nz = %f\n", lol.n.x, lol.n.y, lol.n.z);
*//*

        matrix a;
        matrix b;

        a.xx = 1;
        a.xy = 2;
        a.xz = 0;

        a.yx = 0;
        a.yy = 3;
        a.yz = 0;

        a.zx = 0;
        a.zy = 0;
        a.zz = 1;

        b = matInverse (a);
        matrix m = a;
        double det = m.xx*(m.yy*m.zz - m.zy*m.yz);
        det += m.yx * (m.xz*m.zy - m.xy*m.zz);
        det += m.zx * (m.xy*m.yz - m.xz * m.yy);


        matrix c = matProduct(a, b);
        printf ("%f %f %f\n", c.xx, c.xy, c.xz);
        printf ("%f %f %f\n", c.yx, c.yy, c.yz);
        printf ("%f %f %f\n", c.zx, c.zy, c.zz);

        point a, b, c;
        a.x = 1; a.y = 0; a.z = 0;
        b.x = 1; b.y = 2; b.z = 0;
        c.x = 0; c.y = 0; c.z = 2;

        facet f = createFacet(a, b, c);

        point d;
        d.x = 0 ; d.y = 0; d.z = 0;

        ray r;
        r.o = d;
        r.v.x = 1; r.v.y = 1; r.v.z = 0.5;
        r.v = normalize (r.v);
        point e = computeIntersection (r, f);

        printf ("%f %f %f\n", e.x, e.y, e.z);
        return 0;
}
*/

