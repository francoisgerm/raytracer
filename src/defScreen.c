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
    vector ZB= ptsToVect(Z,entree->screenB) ;
    vector ZO= ptsToVect(Z,entree->obs) ;
    vector ZA= ptsToVect(Z,entree->screenA) ;
    vector AB = ptsToVect(entree->screenA,entree->screenB) ;
    vector AO = ptsToVect(entree->screenA,entree->obs) ;
    
    w=entree->width ;
    h=entree->height ;

    //on récupére les éléments qui ne varient pas
    sortie.width= w ;
    sortie.height= h ;
    sortie.s=entree.s ;
    sortie.back=entree.back ;
    sortie.facets=entree.Facets ;
    sortie.screenA= entree->screenA ;
    sortie.obs = entree->obs ;
    sortie.depth = 1 ; // on le met à 1 pour l'instant
    
    // Calcule de size_x, size_y, size_z
	double size_x = 0.0;
	double size_y = 0.0;
	double size_z = 0.0;

	flist* tmp = entree->Facets;
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

    sortie.size_x=size_x ;
    sortie.size_y=size_y ;
    sortie.size_z=size_z ;
    
    
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
    
    AH=normalize(crossProduct(AO,AB_prim)) ;
    AI= vSum(eDot((h/2.0),AH) , eDot(-(w/2.0),AB_prim)) ;
        
    sortie.top_lefthand =vSum(ZA,AI) ;
    //jusque là ca fonctionne
    i=normalize(AB_prim);
    j=normalize(eDot(-1.0,AH));
    sortie.i=i ;
    sortie.j=j ;
    
    
    
    
    return (sortie);
}   
