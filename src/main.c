#include <stdio.h>
#include <stdlib.h>

#include "divisions.h"
#include "flist.h"
#include "geometry.h"
#include "intersection.h"
#include "misc.h"
#include "moveRay.h"
#include "display.h"
#include "imgsdl.h"
#include "entry.h"
#include "defScreen.h"



int main (int argc, char* argv) {

	printf ("settings...\n");
	settings set = defScreen ("scenes/cubes.scn");

	flist* facets = set.facets;

	while (facets->next != NULL) {
		printf ("list of facet : %f \n", facets->f->a.x);
		facets = facets->next;
	}

	printf ("Initializing the scene...\n");
	box space = initialize (set);

	printf ("Scene initialized !\n");

	SDL_Init (SDL_INIT_VIDEO);

	SDL_Surface* sdl_screen = SDL_SetVideoMode (200, 200, 32, SDL_HWSURFACE);
	SDL_FillRect (sdl_screen, NULL, SDL_MapRGB(sdl_screen->format, 0, 0, 0));

	for (int i = 1; i < set.height; i++) {
		for (int j = 1; j < set.width; j++) {

			printf ("-> Coloring pixel %d %d\n", i, j);

			color whatup = getPixelColor (i, j, set, space);

			printf ("-> Color : %d %d %d\n", whatup.r, whatup.g, whatup.b);

			SDL_Surface* rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);

			SDL_FillRect(rectangle, NULL, SDL_MapRGB(sdl_screen->format,whatup.r, 	whatup.g, whatup.b));

			SDL_Rect position;
			position.x = i;
			position.y = j;
			SDL_BlitSurface(rectangle, NULL, sdl_screen, &position);





			SDL_Flip(sdl_screen);
		}
	}

	sleep(200);

	SDL_Quit ();





	return 0;
}
