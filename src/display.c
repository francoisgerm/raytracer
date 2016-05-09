#include "display.h"

color getRayColor (ray r, settings s, box space, int refl) {
	
	color color_back = s.back;
	color black; black.r = 0; black.g = 0; black.b = 0;
	color new_color;
	color light_color = s.s.cp;
	color diffused_color ; diffused_color.r = 0 ; diffused_color.g = 0 ; diffused_color.b = 0; 
	color reflected_color ; reflected_color.r = 0 ; reflected_color.g = 0 ; reflected_color.b = 0;

	point obs = s.obs;
	point light = s.s.p;

	facet* next_collision = nextIntersection (s, r);


	if (next_collision != NULL) {

		point collision_point = computeIntersection (r, *next_collision);

		vector light_direction = ptsToVect (collision_point, light);

				// we compute the color just in case
				float coeff = 1-next_collision->k;	
				coeff /= 255;
				// fabs so the normal is the right one
				coeff *= fabs(dotProduct(normalize(light_direction),next_collision->n));
			
				

				new_color.r = next_collision->cp.r * light_color.r * coeff;
				new_color.g = next_collision->cp.g * light_color.g * coeff;
				new_color.b = next_collision->cp.b * light_color.b * coeff;



		// -----------------
		// DIFFSED RAY		
		// ---------------
		ray diffused_ray;
		diffused_ray.o = collision_point;
		diffused_ray.v = light_direction;



		// check that we're on the right side of the facet
		if (sameSide (*next_collision, light, obs)) {
			facet* before_light_collision = nextIntersection (s, diffused_ray);
			if (before_light_collision == NULL) { 
				diffused_color = new_color;	

			} else { // there's a facet in the way, need to check that it's behind the light
				// ----------------------------
				// IF TRANSPARENCY ADD HERE !!
				// ----------------------------

				point new_collision = computeIntersection (diffused_ray, *before_light_collision);
				
				vector coll_to_ray = ptsToVect (new_collision, collision_point);

				if (norma(coll_to_ray) <= norma(light_direction)) // it's an obstacle
					diffused_color = black;
				else  // the facet is behind the light
					diffused_color = new_color;	

			}
	
		} else {
			diffused_color = black;
		}
		




		// ---------------------
		// REFLECTED RAY
		// ---------------------
		if (refl < 10) {
			if (next_collision->k > 10e-7) {
				ray reflected_ray;
				reflected_ray.o = collision_point;
		
				vector v_norm = eDot(dotProduct(r.v, next_collision->n), next_collision->n);
		
				reflected_ray.v = eDot( -1.0, vSum( eDot (2.0, v_norm), eDot(-1.0, r.v))); // -1 bc BEFORE the facet
				
		
				if (nextIntersection (s, reflected_ray) != NULL) {
			//		if (refl < 10) {
						reflected_color = getRayColor (reflected_ray, s, space, refl + 1); 
						reflected_color.r = next_collision->k * reflected_color.r;
						reflected_color.g = next_collision->k * reflected_color.g;
						reflected_color.b = next_collision->k * reflected_color.b;
				//	}
				} else {
					reflected_color = color_back;
					reflected_color.r = next_collision->k * reflected_color.r;
					reflected_color.g = next_collision->k * reflected_color.g;
					reflected_color.b = next_collision->k * reflected_color.b;
		
				}
			}
		}
		
		
		// ---------------------
		// REFRACTED RAY
		// ---------------------




	} else { // no collision
		diffused_color = color_back;
	}

	color return_color;
	return_color.r = diffused_color.r + reflected_color.r;
	return_color.g = diffused_color.g + reflected_color.g;
	return_color.b = diffused_color.b + reflected_color.b;


	return return_color;
}



color getPixelColor (int x, int y, settings s, box space) {

	point top_lefthand = s.top_lefthand;
	
	point obs = s.obs;

	int res_x = s.width_px;
	int res_y = s.height_px; // actually width & height in normal mode


	vector i_screen = s.i;
	vector j_screen = s.j;

	point pixel = vSum(top_lefthand, eDot(s.width_scn * x / res_x, i_screen)); 
	pixel = vSum(pixel, eDot(s.height_scn * y / res_y, j_screen)); 


	vector ray_direction = ptsToVect (obs, pixel);
	ray r;
	r.o = pixel;// obs
	r.v = ray_direction;

	return getRayColor (r,s,space,0);

}
