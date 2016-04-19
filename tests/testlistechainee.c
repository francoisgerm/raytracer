#include "divisions.h"
#include "flist.h"
#include "geometry.h"
#include "intersection.h"
#include "misc.h"
#include "moveRay.h"
#include <stdio.h>


int main (void) {
  point a; a.x= 2; a.y= 2; a.z = 4;
  point b; b.x= 4; b.y= 2; b.z = 2;
  point c; c.x= 3; c.y= 4; c.z = 4;
  point d; d.x= 0.5; d.y= 0; d.z = 0;
  point e; e.x= 0; e.y= 0.5; e.z = 0;
  point f; f.x= 0.5; f.y= 0; f.z = 1;
  point g; g.x= 0; g.y= 5; g.z = 4;
  point h; h.x= 4; h.y= 2; h.z = 5;
  point i; i.x= 1; i.y= 6; i.z = 0;
  point j; j.x= 5; j.y= 4; j.z = 3;
  point k; k.x= 2; k.y=-5; k.z = 5;
  point l; l.x= 4; l.y= 3; l.z = 1;



  point x; x.x= 1; x.y= 0; x.z = 0;
  point y; y.x= 0; y.y= 1; y.z = 0;
  point z; z.x= 1; z.y= 0; z.z = 1;

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
	box space = initialize (7, 7, 7,1, &facets);
	

	settings set;
	set.size_x = 7;
	set.size_y = 7;
	set.size_z = 7;
	set.depth = 1;

	ray r;
	point o2;
	o2.x = 0; o2.y = 0; o2.z = 0;

	vector v;
	v.x = 2.0/3.0; v.y = 1.0; v.z = 0.2;

	r.o = o2;
	r.v = v;

	printf ("listechainee.c l.96");
	int* boxes = boxesInPath (set, r);

	int w = 0;

	printf ("listechainee.c l.100");

	while (w < boxes[0]) {
		printf ("BOX NO %d : %d %d %d\n", w, boxes[3*w+1], boxes[3*w+2],boxes[3*w+3]);
		w++;

	}


		printf ("loolll\n");
		facet* fa = space[0][0][0]->f;
		printf ("%f \n", fa->a.x);
		printf ("loolll\n");



	printf ("lol");
	facet* nex_f = nextIntersection (space, set, r);

	if (nex_f != NULL) {
		printf ("nextintersec : %s\n", nex_f->name);
	} else {
		printf ("no facet :(\n");
	}


	point lolilol = computeIntersection (r, m);
	printf ("%f %f %f \n", lolilol.x, lolilol.y, lolilol.z);

	if (isInFacet (lolilol, m)) {
			printf ("actually yes biatch\n");
	} else {
			printf ("no intersec indeed \n");
	}

	return 0;
}
