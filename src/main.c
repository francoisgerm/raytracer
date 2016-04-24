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
	settings set = defScreen ("scenes/mirror.scn");


	printfPoint ("top_left", set.top_lefthand);
	printfPoint ("i", set.i);
	printfPoint ("j", set.j);
	printfPoint ("obs", set.obs);
	printfPoint ("a", set.screenA);
	printfPoint ("b", set.screenB);

	printf ("Size x : %f\n", set.size_x);
	printf ("Size y : %f\n", set.size_y);
	printf ("Size z : %f\n", set.size_z);

	flist* facets = set.facets;

	int i = 1;
	while (facets->next != NULL) {
		printf ("Facet no %d :\n", i);
		printfPoint (" -> a", facets->f->a);
		printfPoint (" -> b", facets->f->b);
		printfPoint (" -> c", facets->f->c);
		facets = facets->next;

		i++;
	}


	printf ("Initializing the scene...\n");
	box space = initialize (set);

	printf ("Scene initialized !\n");

	SDL_Init (SDL_INIT_VIDEO);

	SDL_Surface* sdl_screen = SDL_SetVideoMode (set.height_px, set.width_px, 32, SDL_HWSURFACE);
	SDL_FillRect (sdl_screen, NULL, SDL_MapRGB(sdl_screen->format, 0, 0, 0));

	for (int i = 1; i < set.height_px; i++) {
		for (int j = 1; j < set.width_px; j++) {


			color whatup = getPixelColor (i, j, set, space);

//			printf ("-> Color : %d %d %d\n", whatup.r, whatup.g, whatup.b);

			SDL_Surface* rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);

			SDL_FillRect(rectangle, NULL, SDL_MapRGB(sdl_screen->format,whatup.r, 	whatup.g, whatup.b));

			SDL_Rect position;
			position.x = i;
			position.y = j;
			SDL_BlitSurface(rectangle, NULL, sdl_screen, &position);



//	sleep (100);


			SDL_Flip(sdl_screen);
//			sleep (1);
		}
	}

	sleep(200);

	SDL_Quit ();





	return 0;
}


