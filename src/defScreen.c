#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"
#include "entry.h"
#include "misc.h"
#include "defScreen.h"
#include "flist.h"
#include "read_entry.h"

// gcc src/defScreen.c src/misc.c -Iinclude -Wall


settings defScreen (char* filename)
{
	
	entry* entree ;
	entree = read(filename) ;
	
	settings sortie ;
	point B_prim, B ;
	double w,h ;
	vector AH,AI ;
	vector i,j ;
	point A ;
	
	
	point Z={0,0,0} ; //correspond à l'origine 
	//on récupére les points de entree
	A.x= (entree->screenA).x;
	A.y= (entree->screenA).y;
	A.z= (entree->screenA).z;
	B.x= entree->screenB.x;
	B.y= entree->screenB.y;
	B.z= entree->screenB.z ;
	
	//création des vecteurs nécessaires
	vector ZA= ptsToVect(Z,entree->screenA) ;
	vector AB = ptsToVect(entree->screenA,entree->screenB) ;
	vector AO = ptsToVect(entree->screenA,entree->obs) ;
	
	w=entree->width ;
	h=entree->height ;

	//on récupére les éléments qui ne varient pas
	sortie.width_px= w ;
	sortie.height_px= h ;

	sortie.s=entree->s ;
	sortie.back=entree->back ;
	sortie.facets=entree->Facets ;
	sortie.screenA= entree->screenA ;
	sortie.obs = entree->obs ;
	sortie.depth = 1 ; // on le met à 1 pour l'instant
	
	// Calcul de size_x, size_y, size_z
	double size_x = 0.0;
	double size_y = 0.0;
	double size_z = 0.0;

	double min_x=INFINITY; double max_x=-1*INFINITY;
	double min_y=INFINITY; double max_y=-1*INFINITY;
	double min_z=INFINITY; double max_z=-1*INFINITY;


	// computes the size of the scene
	flist* tmp = entree->Facets;
	while (tmp != NULL) {
		min_x = min2(tmp->f->a.x, min_x);
		min_x = min2(tmp->f->b.x, min_x);
		min_x = min2(tmp->f->c.x, min_x);

		min_y = min2(tmp->f->a.y, min_y);
		min_y = min2(tmp->f->b.y, min_y);
		min_y = min2(tmp->f->c.y, min_y);

		min_z = min2(tmp->f->a.z, min_z);
		min_z = min2(tmp->f->b.z, min_z);
		min_z = min2(tmp->f->c.z, min_z);

		max_x = -1.0 * min2( -1.0 *tmp->f->a.x, -1.0 * max_x);
		max_x = -1.0 * min2( -1.0 *tmp->f->b.x, -1.0 * max_x);
		max_x = -1.0 * min2( -1.0 *tmp->f->c.x, -1.0 * max_x);

		max_y = -1.0 * min2( -1.0 *tmp->f->a.y, -1.0 * max_y);
		max_y = -1.0 * min2( -1.0 *tmp->f->b.y, -1.0 * max_y);
		max_y = -1.0 * min2( -1.0 *tmp->f->c.y, -1.0 * max_y);

		max_z = -1.0 * min2( -1.0 *tmp->f->a.z, -1.0 * max_z);
		max_z = -1.0 * min2( -1.0 *tmp->f->b.z, -1.0 * max_z);
		max_z = -1.0 * min2( -1.0 *tmp->f->c.z, -1.0 * max_z);

		tmp = tmp->next;

	}
	
	point light = sortie.s.p;
	min_x = min2(light.x, min_x);
	min_y = min2(light.y, min_y);
	min_z = min2(light.z, min_z);

	max_x = -1.0 * min2(-1.0 * light.x, -1.0*max_x);
	max_y = -1.0 * min2(-1.0 * light.y, -1.0*max_y);
	max_z = -1.0 * min2(-1.0 * light.z, -1.0*max_z);


	sortie.size_x = (max_x - min_x) + 1.0;
	sortie.size_y = (max_y - min_y) + 1.0;
	sortie.size_z = (max_z - min_z) + 1.0;
	
	
	// on vérifie que le point B appartient bien au plan contenant A et de normal AO
	if (0!=dotProduct(AB,AO))
			{
			//B_prim est la projection de B sur le plan 
			double X ,Y ,Z, D ;
			double t;
			
			//http://www.les-mathematiques.net/phorum/read.php?2,254990,254992
			D=A.x*AO.x + A.y*AO.y + A.z*AO.z ;
			
			t=-(AO.x*B.x + AO.y*B.y + AO.z*B.z - D)/(AO.x*AO.x + AO.y*AO.y + AO.z*AO.z) ;
			X= B.x + AO.x*t ;
			Y= B.y + AO.y*t ;
			Z= B.z + AO.z*t ;
			
			B_prim.x=X ;
			B_prim.y=Y ;
			B_prim.z=Z ;
			sortie.screenB= B_prim ;
			}
	else 
			{
			sortie.screenB=entree->screenB ; 
			}
	 
	vector AB_prim=ptsToVect(A,sortie.screenB) ;
	
	AH=normalize(crossProduct(AO,AB_prim));
	
	double pixel_o_cm = (w / norma(AB_prim))/2.0;
	AI= vSum(eDot((h/2.0)/pixel_o_cm ,AH) , eDot(-1.0,AB_prim)) ;
			
	sortie.top_lefthand =vSum(ZA,AI) ;
	i=normalize(AB_prim);
	j=normalize(eDot(-1.0,AH));
	sortie.i=i ;
	sortie.j=j ;
	
	
	sortie.width_scn = w/pixel_o_cm;
	sortie.height_scn = h/pixel_o_cm;
	
	
	return (sortie);
}   
