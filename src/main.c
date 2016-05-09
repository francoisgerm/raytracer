#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



int main (int argc, char** argv) {

	printf ("Reading scene file...\n");

	char* filename;

	if (argc > 1) {
		filename = malloc ((strlen(argv[1])+1) *sizeof(char));
		filename = argv[1];
	} else {
		filename = malloc (18*sizeof(char));
		filename = "scenes/mirror.scn";
	}
	settings set = defScreen (filename);




	box space = initialize (set);


/*	SDL_Init (SDL_INIT_VIDEO);

	SDL_Surface* sdl_screen = SDL_SetVideoMode (set.height_px, set.width_px, 32, SDL_HWSURFACE);
	SDL_FillRect (sdl_screen, NULL, SDL_MapRGB(sdl_screen->format, 0, 0, 0));
*/

	FILE* output = fopen ("img/image.ppm", "w+");
	if (NULL == output)
		return -1;

	fprintf (output, "P3\n");
	fprintf (output, "%d %d %d\n", (int) set.width_px, (int) set.height_px, 255);



	printf ("Generating scene...\n");
	for (int i = 0; i < set.width_px; i++) {
		for (int j = 0; j < set.height_px; j++) {


			color whatup = getPixelColor (j, i, set, space);

			fprintf (output, "%d %d %d ", whatup.r, whatup.g, whatup.b);

/*
			SDL_Surface* rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);

			SDL_FillRect(rectangle, NULL, SDL_MapRGB(sdl_screen->format,whatup.r, 	whatup.g, whatup.b));

			SDL_Rect position;
			position.x = i;
			position.y = j;
			SDL_BlitSurface(rectangle, NULL, sdl_screen, &position);


			SDL_Flip(sdl_screen);*/
		}
			fprintf (output, "\n");
	}


	printf ("Scene generated, saving in img/image.ppm\n");
	fclose(output);

	//SDL_Quit ();


	printf ("Saving complete, exiting\n");

	return 0;
}


