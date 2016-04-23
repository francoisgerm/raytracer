#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"
#include "entry.h"
#include "misc.h"
#include "defScreen.h"
#include "flist.h"


// gcc src/defScreen.c src/misc.c -Iinclude -Wall


screen defScreen (entry* entree)
{
    screen sortie ;
    point B_prim, B ;
    double w,h ;
    vector AH,AI ;
    vector i,j ;
    point A ;
    double mem ;
    
    
    point Z={0,0,0} ; //correspon à l'origine 
    A.x= (entree->screenA).x;
    A.y= (entree->screenA).y;
    A.z= (entree->screenA).z;
    B.x= entree->screenB.x;
    B.y= entree->screenB.y;
    B.z= entree->screenB.z ;
    vector ZB= ptsToVect(Z,entree->screenB) ;
    vector ZO= ptsToVect(Z,entree->obs) ;
    vector ZA= ptsToVect(Z,entree->screenA) ;
    
    
    w=entree->width ;
    h=entree->height ;

    sortie.width= w ;
    sortie.height= h ;
    
    vector AB = ptsToVect(entree->screenA,entree->screenB) ;
    vector AO = ptsToVect(entree->screenA,entree->obs) ;
    
    sortie.screenA= entree->screenA ;
    sortie.obs = entree->obs ;
    
    // on vérifie que le point B appartient bien au lpan contenant A et de normal AO
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

    //printf(" AI.x : %lf \n", AI.x) ;
    //printf(" AI.y : %lf \n", AI.y) ;
    //printf(" AI.z : %lf \n", AI.z) ;
        
    sortie.top_lefthand =vSum(ZA,AI) ;
    //jusque là ca fonctionne
    i=normalize(AB_prim);
    j=normalize(eDot(-1.0,AH));
    sortie.i=i ;
    sortie.j=j ;
    
    return (sortie);
}   
