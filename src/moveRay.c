#include "moveRay.h"

#include <stdio.h>

facet* nextIntersection (settings s, ray r) {
	flist* facets = s.facets;

	facet* next_facet = NULL;
	double pos = INFINITY;
	while (facets != NULL) {
		point intersection = computeIntersection(r, *(facets->f));

		if (isInFacet (intersection, *(facets->f))) {
			point inter_to_origin = vSum (intersection, eDot(-1, r.o)); // = ->(OI)	
			double pos_bis = -1.0;

			if(fabs(r.v.x) > 10e-7)
				pos_bis = inter_to_origin.x / r.v.x;
			else if (fabs(r.v.y) > 10e-7)
				pos_bis = inter_to_origin.y / r.v.y;
			else if (fabs(r.v.z) > 10e-7)
				pos_bis = inter_to_origin.z / r.v.z;;
			
			if (pos_bis <= pos && pos_bis > 10e-7) {
				pos = pos_bis;
				next_facet = facets->f;
			}
		}

		facets = facets->next;
	}

	return next_facet;
	
}
/*
facet* nextIntersection (box space, settings s, ray r) {

	//printf ("\nnextIntersection\n-------------\n");
	flist* f_in_boxes = getPotFacets (space, s, r);

	//printf ("\nnextIntersection : we have the potential facets\n");

	facet* next_facet = NULL;
	double pos = INFINITY;

	//printf ("  -> loop over the facets in the box\n");
	int index=1;
	while (f_in_boxes != NULL) {
		//printf ("    -> facet %d\n", index);
		index++;
		//printfPoint ("a", f_in_boxes->f->a); 
		//printfPoint ("b", f_in_boxes->f->b); 
		//printfPoint ("c", f_in_boxes->f->c); 

		point intersection = computeIntersection(r,*(f_in_boxes->f));


		//printf ("    -> intersection point :");
		//printf (" %f %f %f\n", intersection.x, intersection.y, intersection.z);

		//printfPoint ("normal", f_in_boxes->f->n);

		//printfPoint ("with ray v", r.v);
		//printfPoint ("with ray o", r.o);
		if (isInFacet (intersection, *(f_in_boxes->f))) { // intersection = pos_bis * v + a

			////printf ("we have intesection with %s\n", f_in_boxes->f->name);
//			sleep(1);
			point inter_to_origin = vSum (intersection, eDot(-1, r.o)); // = ->(OI)	
			double pos_bis = -1.0;


			if(fabs(r.v.x) > 10e-7) {
				pos_bis = inter_to_origin.x / r.v.x;
				////printf ("%f ; %f\n", pos_bis, inter_to_origin.x / r.v.x);
			} else if (fabs(r.v.y) > 10e-7) {
				pos_bis = inter_to_origin.y / r.v.y;
				////printf ("%f ; %f\n", pos_bis, inter_to_origin.y / r.v.y);
			
			} else if (fabs(r.v.z) > 10e-7) {
				pos_bis = inter_to_origin.z / r.v.z;;
				////printf ("%f ; %f\n", pos_bis, inter_to_origin.z / r.v.z);
			}


			////printf ("new t = %f\n", pos_bis);
			if (pos_bis <= pos && pos_bis > 10e-7) {
				pos = pos_bis;
				next_facet = f_in_boxes->f;
			}
		}	else {
	//		//printf("No intersection with pot facet '%s' \n", f_in_boxes->f->name);
		}
		f_in_boxes = f_in_boxes->next;

	//	//printf ("end of loop un nextIntersection \n");
	}
//	//printf (" end of nextIntersection\n");

	return next_facet;
}
*/

/*
flist* getPotFacets (box space, settings s, ray r) {
	////printf ("\ngetPotFacets\n---------\n");
	int* boxes = boxesInPath (s, r);

	////printf ("-> We have the boxes in the path\n");

	flist* facets = malloc(sizeof(flist));
	////printf ("/!\\ Unfreed memory in getFacetsInBoxes(box, settings, ray)\n");
	facets->next = NULL;
	int n_facets = 0;
	int i = 0;

	////printf ("-> starting loop on boxes\n");

	while (i < boxes[0]) {
		////printf ("   -> i = %d && box : %d %d %d\n\n\n",boxes[0],boxes[3*i+1],boxes[3*i+2],boxes[3*i+3]);

		facet* f = space[0][0][0]->f;
		////printf ("    -> first facet a.x : %f \n", f->a.x);
		flist* tmp = space[boxes[3*i+1]][boxes[3*i+2]][boxes[3*i+3]];
		////printf ("    -> tmp flist ok\n    -> loop over the facets in the box\n");
		int index = 1;
		while (tmp != NULL) { // TMP->NEXT BEFORE !!!
			//printf ("      -> facet %d\n", index);
			index++;

			//printfPoint ("        a", tmp->f->a);
			//printfPoint ("        b", tmp->f->b);
			//printfPoint ("        c", tmp->f->c);

			if (n_facets == 0) {
				
			////printf ("FIRST TMP NAME = %s\n", tmp->f->name);
				facets->f = tmp->f;
				facets->next == NULL;
				n_facets ++;
			} else {
			////printf (" SECONDTMP NAME = %s\n", tmp->f->name);
				facets = addOnTop (facets, tmp->f);
				n_facets ++;
			}
			tmp = tmp->next;
		}

		i++;
	}
	////printf ("end of getPotFacets\n");



	//printf (" \n -> list of potential facets \n");
	facets = facets->next;
	int index = 1;
	flist* tmp_f = facets;
	while (tmp_f != NULL) {
		//printf ("    -> facet %d\n", index);
		index++;
		//printfPoint ("      a", tmp_f->f->a);
		//printfPoint ("      b", tmp_f->f->b);
		//printfPoint ("      c", tmp_f->f->c);
		tmp_f = tmp_f->next;
	}
	////printf (" end of potFacets \n");

	free (boxes);

	return facets;
}

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

}*/


/*
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

	//printf ("\nboxesInPath\n--------\n");

	int* boxes_crossed = malloc(4*sizeof(int));
//	//printf ("/!\\ Unfreed memory in boxesInPath(settings, ray)\n");

	ray r2 = r;


	boxes_crossed[1] = fabs(getBoxId (s, r)[0]);
	boxes_crossed[2] = fabs(getBoxId (s, r)[1]);
	boxes_crossed[3] = fabs(getBoxId (s, r)[2]);

	int nb_boxes = 1;

	//printf ("-> ray : %f %f %f\n\n\n", r.v.x, r.v.y, r.v.z);

	//printf ("-> new box %d %d %d\n", boxes_crossed[1], boxes_crossed[2], boxes_crossed[3]);

	while (inScene(s, r2.o)) { 

			// moving the ray to the next box
			double t = nextBoxT(s, r2);
	//		//printf ("t = %f \n", t);
	//		//printf ("%f %f %f\n=============\n\n", r2.v.x, r2.v.y, r2.v.z);

			r2.o = vSum (r2.o, eDot (t, r2.v));
			int* next_box = getBoxId (s,r2);

			if (inScene(s, r2.o) && next_box[0] < s.depth && next_box[1] < s.depth && next_box[2] < s.depth) {

			////printf ("MOVED POSITION = ");
			//	//printf ("%f %f %f\n=============\n\n", r2.o.x, r2.o.y, r2.o.z);
			//	//printf ("inScene : %d\n\n", inScene(s, r2.o));


				boxes_crossed = realloc (boxes_crossed,(3*(1 +nb_boxes) +1)*sizeof(int));

			

				boxes_crossed[3*nb_boxes +1] = next_box[0];
				boxes_crossed[3*nb_boxes +2] = next_box[1];
				boxes_crossed[3*nb_boxes +3] = next_box[2];
				nb_boxes ++;


	//			//printf ("New box : %d %d %d \n===============\n", next_box[0], next_box[1],next_box[2]);
			}
	}
	
	boxes_crossed[0] = nb_boxes;
	return boxes_crossed;

}



*/
