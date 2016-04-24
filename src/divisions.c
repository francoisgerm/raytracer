#include "divisions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

box initialize (settings s){
	int size_x = s.size_x;
	int size_y = s.size_y;
	int size_z = s.size_z;
	int depth = s.depth;
	flist* facets = s.facets;
	//printf ("Initialization...\n");

	box space = malloc (depth * sizeof (flist***));


	//printf ("-> Creating space...\n");
	for (int i = 0; i < depth ; i++) {
		space[i] = malloc (depth * sizeof(flist**));
		for (int j = 0; j < depth; j++) {
			space[i][j] = malloc (depth * sizeof(flist*));
			for (int k = 0; k < depth; k++) {
				space[i][j][k] = malloc(sizeof(flist));

				space[i][j][k]->f = malloc (sizeof(facet*));
				space[i][j][k]->f->a.x = 51;
				space[i][j][k]->f->a.y = 16;
				//printf (" | -> Check-up %d %d %d...\n", i, j, k);

				
			}
		}
	}
	//printf (" => Space created !\n");
	//printf ("-> Assigning facets...\n");
	for (int i= 0; i < depth; i++) {
		for (int j = 0; j < depth; j++) {
			for (int k = 0; k < depth; k++) {
				//printf (" | -> Check-up %d %d %d...\n", i, j, k);
				flist* tmp = facets;
				//printf (" | Temporary list created...\n");
				while (tmp != NULL) { 
					//printf (" | -> Next facet in list...\n");

//printfPoint("a", tmp->f->a);
//printfPoint("b", tmp->f->b);
//printfPoint("c", tmp->f->c);
					if (isInBox (i, j, k, depth, size_x, size_y, size_z, tmp->f)) {
							//printf ("    | New Facet !\n");
							space[i][j][k] = addOnTop(space[i][j][k], tmp->f);



					}
					tmp = tmp->next;
				}
			}
		}
	}

	//printf (" => Initialization done !\n");

	//printf ("Checking initialization... \n");

	for (int i = 0; i < depth; i++) {
		for (int j = 0; j < depth; j++) {
			for (int k = 0; k < depth; k++) {
				flist *tmp;
				tmp = space[i][j][k];
				//printf ("==> Box : %d %d %d\n", i, j, k);
				while (tmp->next != NULL) {
			//			//printf ("   --> facet %s\n", tmp->f->name);
///						sleep(1);
						tmp = tmp->next;
				}
			}
		}
	}
	return space;
}


int isInBox (int i, int j, int k, int depth, int size_x, int size_y, int size_z, facet* f) {
	double coeff_x = (double) depth / ((double) size_x);
	double coeff_y = (double) depth / ((double) size_y);
	double coeff_z = (double) depth / ((double) size_z);
	
	int x_a = (int) floor ( (double) f->a.x * coeff_x);
	int y_a = (int) floor ( (double) f->a.y * coeff_y);
	int z_a = (int) floor ( (double) f->a.z * coeff_z);

	int x_b = (int) floor ( (double) f->b.x * coeff_x);
	int y_b = (int) floor ( (double) f->b.y * coeff_y);
	int z_b = (int) floor ( (double) f->b.z * coeff_z);

	int x_c = (int) floor ( (double) f->c.x * coeff_x);
	int y_c = (int) floor ( (double) f->c.y * coeff_y);
	int z_c = (int) floor ( (double) f->c.z * coeff_z);


	//printf ("a : %d %d %d\n", x_a, y_a, z_a);
	//printf ("b : %d %d %d\n", x_b, y_b, z_b);
	//printf ("c : %d %d %d\n", x_c, y_c, z_c);

	if (x_a == i && y_a == j && z_a == k)
		return 1;
	if (x_b == i && y_b == j && z_b == k)
		return 1;
	if (x_c == i && y_c == j && z_c == k)
		return 1;

	return 0;

}

int* getBoxId (settings s, ray r) {
	if (s.depth == 1) {
		int* id = malloc(3*sizeof(int));
		id[0] = 0; id[1] = 0; id[2] = 0;
		return id;
	}

	//printf ("size x : %f\n", s.size_x);

	//printf ("size y : %f\n", s.size_y);

	//printf ("size z : %f\n", s.size_z);
	double coeff_x = (double) s.depth / ((double) s.size_x);
	double coeff_y = (double) s.depth / ((double) s.size_y);
	double coeff_z = (double) s.depth / ((double) s.size_z);
	
	int x_o = (int) floor ( (double) fabs(r.o.x) * coeff_x);
	int y_o = (int) floor ( (double) fabs(r.o.y) * coeff_y);
	int z_o = (int) floor ( (double) fabs(r.o.z) * coeff_z);


	int* id = malloc (3* sizeof(int));
//	//printf ("/!\\ Unfreed memory in getBoxId(settings, ray)\n");
	
	id[0] = x_o;
	id[1] = y_o;
	id[2] = z_o;


	////printf ("x : %f, box : %d\n", r.o.x, x_o);
//	//printf ("y : %f, box : %d\n", r.o.y, y_o);
//	//printf ("z : %f, box : %d\n", r.o.z, z_o);


	return id;

}



int sameBox (int* b1, int* b2) {
	for (int i = 0; i < 3; i++)
		if (b1[i] != b2[i])
			return 0;
	return 1;
}
