#include "divisions.h"
#include "flist.h"
#include "geometry.h"
#include "intersection.h"
#include <stdio.h>


int main (void) {
  point a; a.x= 2; a.y= 2; a.z = 4;
  point b; b.x= 4; b.y= 2; b.z = 2;
  point c; c.x= 3; c.y= 4; c.z = 4;
  point d; d.x= 2; d.y= 4; d.z = 2;
  point e; e.x= 6; e.y= 1; e.z = 3;
  point f; f.x= 3; f.y= 4; f.z = 2;
  point g; g.x= 0; g.y= 5; g.z = 4;
  point h; h.x= 4; h.y= 2; h.z = 5;
  point i; i.x= 1; i.y= 6; i.z = 0;
  point j; j.x= 5; j.y= 4; j.z = 3;
  point k; k.x= 2; k.y=-5; k.z = 5;
  point l; l.x= 4; l.y= 3; l.z = 1;



  point x; x.x= 0; x.y= 0; x.z = 0;
  point y; y.x= 0.5; y.y= 0.5; y.z = 0.5;
  point z; z.x= 0; z.y= 0.2; z.z = 0.31;

  facet m = createFacet(x, y, z);
  facet n = createFacet(d, e, f);
  facet o = createFacet(g, h, i);
  facet q = createFacet(a, e, i);
  facet s = createFacet(c, e, g);
  facet t = createFacet(f, h, j);


	m.name = "m";
	n.name = "n";
	o.name = "o";
	q.name = "q";
	s.name = "s";
	t.name = "t";

	printf ("Ordering the facets...\n");
	flist facets;
	printf (" -> Check-up 1... \n");
	facets.f = &m;

	

	printf (" -> Check-up 2... \n");
	flist facet2;
	facet2.f = &n;
	facets.next = &facet2;

	flist facet3;
	facet3.f = &o;
	facet2.next = &facet3;

	flist facet4;
	facet4.f = &q;
	facet3.next = &facet4;

	flist facet5;
	facet5.f = &s;
	facet4.next = &facet5;

	flist facet6;
	facet6.f = &t;
	facet5.next = &facet6;

	facet6.next = NULL;


	printf ("Initializing the scene...\n");
	box space = initialize (7, 7, 7,3, &facets);
	



	return 0;
}
