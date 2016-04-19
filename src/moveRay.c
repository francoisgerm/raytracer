#include "moveRay.h"

#include <stdio.h>

facet* nextIntersection (box space, settings s, ray r) {

	printf ("Welcome in nextIntersection\n");
	flist* f_in_boxes = getPotFacets (space, s, r);

	printf ("We have the facets !!!\n\n\n");

	facet* next_facet = NULL;
	double pos = INFINITY;

	while (f_in_boxes != NULL) {


		printf ("Facet : %s \n", f_in_boxes->f->name);
		point intersection = computeIntersection(r,*(f_in_boxes->f));


		if (isInFacet (intersection, *(f_in_boxes->f))) { // intersection = pos_bis * v + a
			printf ("We have intersected !\n");
			point inter_to_origin = vSum (intersection, eDot(-1, r.o));	
			double pos_bis = -1.0;


			if(fabs(r.v.x) > 10e-7)
				pos_bis = inter_to_origin.x;
			else if (fabs(r.v.y) > 10e-7)
				pos_bis = inter_to_origin.y;
			else if (fabs(r.v.z) > 10e-7)
				pos_bis = inter_to_origin.z;


			printf ("new t = %f\n", pos_bis);
			if (pos_bis <= pos && pos_bis > 10e-7) {
				pos = pos_bis;
				next_facet = f_in_boxes->f;
			}
		}	else {
			printf("No intersection with pot facet '%s' \n", f_in_boxes->f->name);
		}
		f_in_boxes = f_in_boxes->next;

		printf ("end of loop un nextIntersection \n");
	}
	printf (" end of nextIntersection\n");

	return next_facet;
}

flist* getPotFacets (box space, settings s, ray r) {
	int* boxes = boxesInPath (s, r);

	printf ("we have the boxes in the path\n");

	flist* facets = malloc(sizeof(flist));
	printf ("/!\\ Unfreed memory in getFacetsInBoxes(box, settings, ray)\n");
	facets->next = NULL;
	int n_facets = 0;
	int i = 0;

	printf ("starting while\n");

	while (i < boxes[0]) {


		printf ("box : %d %d %d\n",boxes[3*i+1],boxes[3*i+2],boxes[3*i+3]);

		facet* f = space[0][0][0]->f;
		printf ("%f \n", f->a.x);
		flist* tmp = space[boxes[3*i+1]][boxes[3*i+2]][boxes[3*i+3]];
		while (tmp->next != NULL) {

			printf ("TMP NAME = %s\n", tmp->f->name);
			if (n_facets == 0) {
				
			printf ("FIRST TMP NAME = %s\n", tmp->f->name);
				facets->f = tmp->f;
				facets->next == NULL;
				n_facets ++;
			} else {
			printf (" SECONDTMP NAME = %s\n", tmp->f->name);
				facets = addOnTop (facets, tmp->f);
				n_facets ++;
			}
			tmp = tmp->next;
		}

		i++;
	}
	printf ("end of getPotFacets\n");



	printf ("LIST OF POTENTIAL FACETS :\n----------------------------\n");
	flist* tmp_f = facets;
	while (tmp_f != NULL) {
		printf ("text  %d \n", n_facets);
		printf ("%s ; ", tmp_f->f->name);
		tmp_f = tmp_f->next;
	}
	printf (" end of potFacets \n");

	return facets;
}


/*
facet* moveRay (box space, settings s, ray r) {
	int* current_box = getBoxId (s, r);
	
	facet* next_facet = NULL;
	while (next_facet == NULL && inScene(s, r.o)) {
		flist* f_in_box = space[current_box[0]][current_box[1]][current_box[2]];
		next_facet = nextFacetInBox (f_in_box, r);
		
		if (next_facet == NULL) {
//			current_box = nextBox (s, r);
//			r = moveRayToNextBox (current_box, r, s);
				r = moveRayToNextBox (r, s);
		}

	}

	return next_facet;
}*/
/*
ray moveRayToNextBox (ray r, settings s) {
	int* box = nextBox (s, r);
	ray new_ray = r;
	double t = 0.0;
	double step = getStep (s, r);

	while (0 == sameBox (box, getBoxId(s,new_ray))) {
	// while (box != getBoxId (s, r)) {
		new_ray.o = vSum(new_ray.o, eDot(t, r.v));
		t += step;		
		printf ("-> Ray advancing in moveRayToNextBox (ray, settings)...\n");

		int* c_box = getBoxId (s, r);
		printf ("Next box : %d %d %d\n", c_box[0], c_box[1], c_box[2]);
		printf ("t = %f \n", t);
		printf ("Original box : %d %d %d\n", box[0], box[1], box[2]);

		printf ("Same box: %d\n", sameBox(box, getBoxId(s, new_ray)));
		sleep(1);

		step = getStep (s, new_ray);
		step /= sqrt(dotProduct(r.v, r.v));
	}

	return new_ray;
}
*/
double nextBoxT (settings s, ray r) {
	
	double coeff_x = (double) s.depth / ((double) s.size_x);
	double coeff_y = (double) s.depth / ((double) s.size_y);
	double coeff_z = (double) s.depth / ((double) s.size_z);
	
	int x_a = (int) floor ( (double) r.o.x * coeff_x);
	int y_a = (int) floor ( (double) r.o.y * coeff_y);
	int z_a = (int) floor ( (double) r.o.z * coeff_z);

	int x_a_bis = r.v.x > 0 ? x_a + 1 : x_a - 1;
	int y_a_bis = r.v.y > 0 ? y_a + 1 : y_a - 1;
	int z_a_bis = r.v.z > 0 ? z_a + 1 : z_a - 1;


	double t_x = fabs(r.v.x)>10e-7 ? (((double) x_a_bis)/coeff_x - r.o.x) /r.v.x:INFINITY;
	double t_y = fabs(r.v.y)>10e-7 ? (((double) y_a_bis)/coeff_y - r.o.y) / r.v.y:INFINITY;
	double t_z = fabs(r.v.z)>10e-7 ? (((double) z_a_bis)/coeff_z - r.o.z) / r.v.z:INFINITY;



	if (t_x == INFINITY && t_y == INFINITY)
		return 2.0*t_z;
	if (t_y == INFINITY && t_z == INFINITY)
		return 2.0*t_x;
	if (t_x == INFINITY && t_z == INFINITY)
		return 2.0*t_y;



	if (t_x <= t_y && t_x <= t_z) 
		if (t_y <= t_z)
			return 0.5 * (t_x + t_y);
		else
			return 0.5 * (t_x + t_z);
	else if (t_y <= t_x && t_y <= t_z){
		if (t_x <= t_z)
			return 0.5 * (t_x + t_y);
		else {
			return 0.5 * (t_z + t_y);

		}
	}
	else if (t_z <= t_x && t_z <= t_y)
		if (t_x <= t_y)
			return 0.5 * (t_x + t_z);
		else
			return 0.5 * (t_z + t_y);
	else 
		return -1.0;

}



double getStep (settings s, ray r) {

	double b_x = floor (r.o.x * s.depth/s.size_x); // box x coord
	double s_b_x = s.size_x / s.depth; // size box x
	double x = r.o.x - b_x * s_b_x;
	
	double b_y = floor (r.o.y * s.depth/s.size_y);	double s_b_y = s.size_y / s.depth;
	double y = r.o.y - b_y * s_b_y;
	
	double b_z = floor (r.o.z * s.depth/s.size_z);
	double s_b_z = s.size_z / s.depth; 
	double z = r.o.z - b_z * s_b_z;

	// (x, y, z) : coordinates as if in the origin box
	double d1 = min2 (fabs(s_b_x - x), x);	// min distance to the border
	double d2 = min2 (fabs(s_b_y - y), y);
	double d3 = min2 (fabs(s_b_z - z), z);

	return min3 (d1, d2, d3) / 2;


}


int* boxesInPath (settings s, ray r) {

	int* boxes_crossed = malloc(4*sizeof(int));
	printf ("/!\\ Unfreed memory in boxesInPath(settings, ray)\n");

	ray r2 = r;


	boxes_crossed[1] = getBoxId (s, r)[0];
	boxes_crossed[2] = getBoxId (s, r)[1];
	boxes_crossed[3] = getBoxId (s, r)[2];

	int nb_boxes = 1;

	while (inScene(s, r2.o)) { 

			// moving the ray to the next box
			double t = nextBoxT(s, r2);

			r2.o = vSum (r2.o, eDot (t, r2.v));
			int* next_box = getBoxId (s,r2);

			if (inScene(s, r2.o)) {

				boxes_crossed = realloc (boxes_crossed,(3*(1 +nb_boxes) +1)*sizeof(int));

			

				boxes_crossed[3*nb_boxes +1] = next_box[0];
				boxes_crossed[3*nb_boxes +2] = next_box[1];
				boxes_crossed[3*nb_boxes +3] = next_box[2];
				nb_boxes ++;
			}
	}
	
	boxes_crossed[0] = nb_boxes;
	return boxes_crossed;

}


