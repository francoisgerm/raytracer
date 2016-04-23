#include <stdio.h>
#include <stdlib.h>
#include "defScreen.h"
#include "geometry.h"
#include "misc.h"
#include "entry.h"

//gcc src/geometry.c src/defScreen.c src/misc.c tests/tests_defScreen.c -Iinclude -Wall -lm


int main ()
{
    entry test_entree ;
    screen test_sortie ;
    screen test_sortie_1 ;
    screen test_sortie_2 ;
    
    //first test
    test_entree.width= 2.0 ;
    test_entree.height= 2.0 ;
    
    test_entree.obs.x= 1;
    test_entree.obs.y= 1;
    test_entree.obs.z= 5;
    
    test_entree.screenA.x= 1;
    test_entree.screenA.y= 1;
    test_entree.screenA.z= 0;

    test_entree.screenB.x= 1;
    test_entree.screenB.y= 2;
    test_entree.screenB.z= 0;
    
    test_sortie = defScreen(&test_entree) ;
    printf("premier test \n \n");
    printf("le nouveau point B est : \n") ;
    printf(" B.x : %lf devrait faire 1\n", test_sortie.screenB.x) ;
    printf(" B.y : %lf devrait faire 2\n", test_sortie.screenB.y) ;
    printf(" B.z : %lf devrait faire 0\n", test_sortie.screenB.z) ;
    printf(" (I.x %lf, I.y %lf, I.z %lf) devrait faire (0,0,0)\n", test_sortie.top_lefthand.x, test_sortie.top_lefthand.y, test_sortie.top_lefthand.z) ;
    printf("vecteur i : i.x =%lf ; i.y=%lf ; i.z=%lf \n", test_sortie.i.x, test_sortie.i.y, test_sortie.i.z ) ;
    printf("vecteur j : j.x =%lf ; j.y=%lf ; j.z=%lf \n \n \n", test_sortie.j.x, test_sortie.j.y, test_sortie.j.z ) ;
    
    //second test
    
    printf("second tests \n");
    test_entree.width= 2.0 ;
    test_entree.height= 2.0 ;
    
    test_entree.obs.x= 1;
    test_entree.obs.y= 1;
    test_entree.obs.z= 5;
    
    test_entree.screenA.x= 1;
    test_entree.screenA.y= 1;
    test_entree.screenA.z= 0;

    test_entree.screenB.x= 1;
    test_entree.screenB.y= 2;
    test_entree.screenB.z= 5;
    
    test_sortie_1 = defScreen(&test_entree) ;
    printf("le nouveau point B est : \n") ;
    printf(" B.x : %lf devrait faire 1\n", test_sortie_1.screenB.x) ;
    printf(" B.y : %lf devrait faire 2\n", test_sortie_1.screenB.y) ;
    printf(" B.z : %lf devrait faire 0\n", test_sortie_1.screenB.z) ;
    printf(" (I.x %lf, I.y %lf, I.z %lf) devrait faire (0,0,0)\n ", test_sortie_1.top_lefthand.x,test_sortie_1.top_lefthand.y,test_sortie_1.top_lefthand.z) ;
    printf("vecteur i : i.x =%lf ; i.y=%lf ; i.z=%lf \n", test_sortie_1.i.x, test_sortie_1.i.y, test_sortie_1.i.z ) ;    
    printf("vecteur j : j.x =%lf ; j.y=%lf ; j.z=%lf \n \n \n", test_sortie_1.j.x, test_sortie_1.j.y, test_sortie_1.j.z ) ;
    
    //third test
    
    printf("troisieme test \n");
    test_entree.width= 2.0 ;
    test_entree.height= 6.0 ;
    
    test_entree.obs.x= 1;
    test_entree.obs.y= 1;
    test_entree.obs.z= 5;
    
    test_entree.screenA.x= 1;
    test_entree.screenA.y= 1;
    test_entree.screenA.z= 0;

    test_entree.screenB.x= 1;
    test_entree.screenB.y= 7;
    test_entree.screenB.z= -5;
    
    test_sortie_2 = defScreen(&test_entree) ;
    printf("le nouveau point B est : \n") ;
    printf(" B.x : %lf devrait faire -4\n", test_sortie_2.screenB.x) ;
    printf(" B.y : %lf devrait faire 5\n", test_sortie_2.screenB.y) ;
    printf(" B.z : %lf devrait faire 0\n", test_sortie_2.screenB.z) ;
    printf(" (I.x %lf, I.y %lf, I.z %lf) devrait faire (0,0,0)\n", test_sortie_2.top_lefthand.x, test_sortie_2.top_lefthand.y, test_sortie_2.top_lefthand.z) ;
    printf("vecteur i : i.x =%lf ; i.y=%lf ; i.z=%lf \n", test_sortie_2.i.x, test_sortie_2.i.y, test_sortie_2.i.z ) ;    
    printf("vecteur j : j.x =%lf ; j.y=%lf ; j.z=%lf \n \n \n", test_sortie_2.j.x, test_sortie_2.j.y, test_sortie_2.j.z ) ;
    
    
    return(0) ;

}
