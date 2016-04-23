#include "display.h"

color getRayColor (ray r, settings s, box space, int refl) {
	// -----------------------------
	// INIT. USELESS IN THE FUTURE
	// -----------------------------
	color color_back; color_back.r = 50; color_back.g = 75; color_back.b = 100; 
	color black; black.r = 0; black.g = 0; black.b = 0;
	color new_color;
	color light_color; light_color.r = 255; light_color.g = 255; light_color.b = 255;
	color diffused_color ; diffused_color.r = 0 ; diffused_color.g = 0 ; diffused_color.b = 0; 
	color reflected_color ; reflected_color.r = 0 ; reflected_color.g = 0 ; reflected_color.b = 0;

	point obs;
	obs.x = 0.5; obs.y =-2.0; obs.z = 0.5;
	point light;
	light.x = 0.5; light.y = 1.0; light.z = 0.5;




	// ------------------
	// REAL CODE
	// ------------------

	
	facet* next_collision = nextIntersection (space, s, r);

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
		vector coll_to_light = ptsToVect (collision_point, light);
		vector coll_to_obs = ptsToVect (collision_point, obs);
		if (sameSide (*next_collision, light, obs)) {
			facet* before_light_collision = nextIntersection (space, s, diffused_ray);
			if (before_light_collision == NULL) { 
				diffused_color = new_color;	

			} else { // there's a facet in the way, need to check that it's behind the light
				// ----------------------------
				// IF TRANSPARENCY ADD HERE !!
				// ----------------------------

				point new_collision = computeIntersection (diffused_ray, *before_light_collision);
				
				vector coll_to_ray = ptsToVect (new_collision, collision_point);

				if (norma(coll_to_ray) <= norma(light_direction)) // it's an obstacle
				{
				printf ("obstacle 1\n");

					diffused_color = black;
				}
				else  // the facet is behind the light
					diffused_color = new_color;	

			}
	
		} else {
			diffused_color = black;
		}
		
		// ---------------------
		// REFLECTED RAY
		// ---------------------
		if (next_collision->k > 10e-7) {
			ray reflected_ray;
			reflected_ray.o = collision_point;
//			reflected_ray.v = vSum (eDot(2.0, next_collision->n), eDot(-1.0, r.v));
	
			vector v_norm = eDot(dotProduct(r.v, next_collision->n), next_collision->n);
//			vector v_facet = vSum (r.v, eDot(-1.0, v_norm));
	
			reflected_ray.v = eDot( -1.0, vSum( eDot (2.0, v_norm), eDot(-1.0, r.v))); // -1 bc BEFORE the facet
			
			printf ("facet : %s\n", next_collision->name);
	
			printfPoint ("incident ray", r.v);
			printfPoint ("reflected ray", reflected_ray.v);
			printfPoint ("normal", next_collision->n);
	
				
			printf ("refl =  %d\n", refl);
	
			if (nextIntersection (space, s, reflected_ray) != NULL) {
				if (refl < 5) {
					reflected_color = getRayColor (reflected_ray, s, space, refl + 1); 
					reflected_color.r = next_collision->k * reflected_color.r;
					reflected_color.g = next_collision->k * reflected_color.g;
					reflected_color.b = next_collision->k * reflected_color.b;
					printf ("we reflect %d\n", refl);
				}
			} else {
				reflected_color = color_back;
				reflected_color.r = next_collision->k * reflected_color.r;
				reflected_color.g = next_collision->k * reflected_color.g;
				reflected_color.b = next_collision->k * reflected_color.b;
	
			}
		}
		
	} else {
		diffused_color = color_back;
	}

	color return_color;
	return_color.r = diffused_color.r + reflected_color.r;
	return_color.g = diffused_color.g + reflected_color.g;
	return_color.b = diffused_color.b + reflected_color.b;


	return return_color;
}

color getPixelColor (int x, int y, settings s, box space) {

	//printf ("\n\nNew ray\n-------\n");

	point top_lefthand;
	top_lefthand.x = 0.0; top_lefthand.y = 0.0; top_lefthand.z = 1;

	point obs;
	obs.x = 0.5; obs.y =-2.0; obs.z = 0.5;
	point light;
	light.x = 0.5; light.y = 1.0; light.z = 0.5;

	int res_x = 200;
	int res_y = 200;


	color color_back;
	color_back.r = 50; 
	color_back.g = 75; 
	color_back.b = 100; 
	color black; black.r = 0; black.g = 0; black.b = 0;
	color new_color;
	color light_color;
	light_color.r = 255; light_color.g = 255; light_color.b = 255;

	vector i_screen;
	i_screen.x = 1.0; i_screen.y = 0.0; i_screen.z = 0.0;
	i_screen = normalize (i_screen);
	vector j_screen;
	j_screen.x = 0.0; j_screen.y = 0.0; j_screen.z = -1.0;
	j_screen = normalize (j_screen);

	point pixel = vSum(top_lefthand, eDot(s.width * x / res_x, i_screen)); 
	pixel = vSum(pixel, eDot(s.height * y / res_y, j_screen)); 


//	printf ("\n ======================== \n");
//	printf ("PIXEL : %f %f %f\n", pixel.x, pixel.y, pixel.z);
	point move_x = eDot(s.width * x / res_x, i_screen);
//	printf ("MOVE X : %f %f %f\n", move_x.x, move_x.y, move_x.z);
	point move_y = eDot(s.height * y / res_y, j_screen); 
//	printf ("MOVE Y : %f %f %f\n", move_y.x, move_y.y, move_y.z);

//	printf ("\n ======================== \n");


	vector ray_direction = ptsToVect (obs, pixel);
	ray r;
	r.o = pixel;// obs
	r.v = ray_direction;
/*
	int reflexions = 0;

	while (reflexions < 4) {
		color tmp_color =  getRayColor (r, s, space);


		
		if(tmp_color == color_back || tmp_color == black)
			reflexions = 10;

		reflexions ++;
	}*/


	return getRayColor (r,s,space,0);;


/*
	facet* next_collision = nextIntersection (space, s, r);

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



		ray diffused_ray;
		diffused_ray.o = collision_point;
		diffused_ray.v = light_direction;


		facet* before_light_collision = nextIntersection (space, s, diffused_ray);

		// check that we're on the right side of the facet
		vector coll_to_light = ptsToVect (collision_point, light);
		vector coll_to_obs = ptsToVect (collision_point, obs);
		if (sameSide (*next_collision, light, obs)) {
			if (before_light_collision == NULL) { 
				return new_color;	

			} else { // there's a facet in the way, need to check that it's behind the light
				// ----------------------------
				// IF TRANSPARENCY ADD HERE !!
				// ----------------------------

				point new_collision = computeIntersection (diffused_ray, *before_light_collision);
				
				vector coll_to_ray = ptsToVect (new_collision, collision_point);

				if (norma(coll_to_ray) <= norma(light_direction)) // it's an obstacle
				{
				printf ("obstacle 1\n");

					return black;
				}
				else  // the facet is behind the light
					return new_color;	

			}
	
		} else {
			return black;
		}
	} else {
		return color_back;
	}
*/

}