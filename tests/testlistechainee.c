#include "divisions.h"
#include "flist.h"
#include "geometry.h"
#include "intersection.h"
#include "misc.h"
#include "moveRay.h"
#include "display.h"
#include <stdio.h>
#include "imgsdl.h"
#include "entry.h"

/*void traceSDLScene (SDL_Surface* display, scene* s) {
  int h = s->height, w = s->width, i, j;
  for (i=0; i<w; ++i)
    for (j=0; j<h; ++j)
      putPixel(display, i, j, i*255/h, (w-j)*255/w, (i+w-j)*255/(w+h));
};
*/



int main (void) {
  point a; a.x= 2; a.y= 2; a.z = 4;
  point b; b.x= 4; b.y= 2; b.z = 2;
  point c; c.x= 3; c.y= 4; c.z = 4;

  point d; d.x= 0.5; d.y= 3; d.z = 0.1;
  point e; e.x= 0; e.y= 4; e.z = 0.1;
  point f; f.x= 0.5; f.y= 3; f.z = 1;
  
	point g; g.x= 0; g.y= 6; g.z = 6;
  point h; h.x= 4; h.y= 2; h.z = 5;
  point i; i.x= 1; i.y= 6; i.z = 0;
  point j; j.x= 5; j.y= 4; j.z = 3;
  point k; k.x= 2; k.y=-5; k.z = 5;
  point l; l.x= 4; l.y= 3; l.z = 1;



  point x; x.x= 0; x.y= 0; x.z = 0;
  point y; y.x= 6; y.y= 0; y.z = 0;
  point z; z.x= 0; z.y= 6; z.z = 0;

  facet m = createFacet(x, y, z);
  facet n = createFacet(d, e, f);
  facet o = createFacet(y, z, g);
  facet q = createFacet(a, e, i);
  facet s = createFacet(c, e, g);
  facet t = createFacet(f, h, j);


	m.name = "m";
	n.name = "n"; // green
	o.name = "o"; // red
	q.name = "q";
	s.name = "s";
	t.name = "t";

	n.cp.r = 0;
	n.cp.g = 255;
	n.cp.b = 0;
	
	o.cp.r = 255;
	o.cp.g = 0;
	o.cp.b = 0;

	o.k = 1;

	m.cp.r = 0;
	m.cp.g = 0;
	m.cp.b = 255;
	m.k = 0;
	n.k = 0;

	


	printf ("Ordering the facets...\n");
	flist facets;
	printf (" -> Check-up 1... \n");
	facets.f = &m;

	

	printf (" -> Check-up 2... \n");
	flist facet2;
	facet2.f = &n;
	facets.next = &facet2;
	facet2.next = NULL;

	flist facet3;
	facet3.f = &o;
	facet2.next = &facet3;
	
	facet3.next = NULL;

	/*

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
*/



	settings set;
	set.size_x = 7;
	set.size_y = 7;
	set.size_z = 7;
	set.depth = 1;
	set.height_scn = 1;
	set.width_scn = 1;
	set.height_px = 200;
	set.width_px = 200;

	set.top_lefthand.x = 0;
	set.top_lefthand.y = 0;
	set.top_lefthand.z = 1;

	set.screenA.x = 0.5;
	set.screenA.y = 0.0;
	set.screenA.z = 0.5;

	set.screenB.x = 1.0;
	set.screenB.y = 0.0;
	set.screenB.z = 0.5;
	
	set.i.x = 1.0;
	set.i.y = 0.0;
	set.i.z = 0.0;

	set.j.x = 0.0;
	set.j.y = 0.0;
	set.j.z = -1.0;

	color back; back.r = 50; back.g = 70; back.b = 150;
	set.back = back;

	source so;
	so.p.x = 0.5; so.p.y = 0.5 ; so.p.z = 0.5;
	so.cp.r = 255; so.cp.g = 255; so.cp.b = 255;
	set.s = so;

	set.obs.x = 0.5 ; set.obs.y = -0.5 ; set.obs.z = 0.5;
	set.facets = &facets;

	printf ("Initializing the scene...\n");
	box space = initialize (set);
	

	SDL_Init (SDL_INIT_VIDEO);

	SDL_Surface* sdl_screen = SDL_SetVideoMode (200, 200, 32, SDL_HWSURFACE);
	SDL_FillRect (sdl_screen, NULL, SDL_MapRGB(sdl_screen->format, 0, 0, 0));

	for (int i = 1; i < 200; i++) {
		for (int j = 1; j < 200; j++) {


		//	printf ("i = %d ; j = %d\n================\n\n", i, j);
			color whatup = getPixelColor (i, j, set, space);

	
	
	
	






			SDL_Surface* rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);

			SDL_FillRect(rectangle, NULL, SDL_MapRGB(sdl_screen->format,whatup.r, 	whatup.g, whatup.b));

			SDL_Rect position;
			position.x = i;
			position.y = j;
			SDL_BlitSurface(rectangle, NULL, sdl_screen, &position);





			SDL_Flip(sdl_screen);
		}
	}

			sleep(20);

	SDL_Quit ();


//			printf ("Color of the ambiance : %d %d %d\n", whatup.r, whatup.g, whatup.b);




/*







// TEST WITH FILES

	entry scene = *read("scenes/cubes.scn");
	flist* n_facets = scene.Facets;
	set.depth = 1;
	set.width = scene.width;
	set.height = scene.height;

	// size_x, size_y, size_z
	double size_x = 0.0;
	double size_y = 0.0;
	double size_z = 0.0;

	flist* tmp = n_facets->f;
	while (tmp != NULL) {
		if (tmp->f.a.x > size_x)
			size_x = tmp->f.a.x;
		if (tmp->f.b.x > size_x)
			size_x = tmp->f.b.x;
		if (tmp->f.c.x > size_x)
			size_x = tmp->f.c.x;

		if (tmp->f.a.y > size_y)
			size_y = tmp->f.a.y;
		if (tmp->f.b.y > size_y)
			size_y = tmp->f.b.y;
		if (tmp->f.c.y > size_y)
			size_y = tmp->f.c.y;

		if (tmp->f.a.z > size_z)
			size_z = tmp->f.a.z;
		if (tmp->f.b.z > size_z)
			size_z = tmp->f.b.z;
		if (tmp->f.c.z > size_z)
			size_z = tmp->f.c.z;

		tmp = tmp->next;
	}

	set.size_x = size_x; set.size_y = size_y ; set.size_z = size_z;
	
	set.back.r = 50;
	set.back.r = 75;
	set.back.r = 100;

	printf ("Initializing the scene...\n");
	box space = initialize (size_x, size_y, size_z,1, &facets);



	screen n_screen = defScreen(&scene);








*/
	return 0;
}
