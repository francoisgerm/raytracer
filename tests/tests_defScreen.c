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
    printf("le nouveau point B est : \n") ;
    printf(" B.x : %lf devrait faire 1\n", test_sortie.screenB.x) ;
    printf(" B.y : %lf devrait faire 2\n", test_sortie.screenB.y) ;
    printf(" B.z : %lf devrait faire 0\n", test_sortie.screenB.z) ;
    printf(" (I.x %lf, I.y %lf, I.z %lf) devrait faire (0,0,0)\n \n \n", test_sortie.top_lefthand.x, test_sortie.top_lefthand.y, test_sortie.top_lefthand.z) ;
    
    //second test
    
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
    printf(" (I.x %lf, I.y %lf, I.z %lf) devrait faire (0,0,0)\n ", test_sortie_1.top_lefthand.x, test_sortie_1.top_lefthand.y, test_sortie_1.top_lefthand.z) ;
    
    
    //third test
    /*
    test_entree.width= 2.0 ;
    test_entree.height= 2.0 ;
    
    test_entree.obs.x= 1;
    test_entree.obs.y= 1;
    test_entree.obs.z= 5;
    
    test_entree.screenA.x= 1;
    test_entree.screenA.y= 1;
    test_entree.screenA.z= 0;

    test_entree.screenB.x= -4;
    test_entree.screenB.y= 5;
    test_entree.screenB.z= -5;
    
    test_sortie_2 = defScreen(&test_entree) ;
    printf("le nouveau point B est : \n") ;
    printf(" B.x : %lf devrait faire -4\n", test_sortie_2.screenB.x) ;
    printf(" B.y : %lf devrait faire 5\n", test_sortie_2.screenB.y) ;
    printf(" B.z : %lf devrait faire 0\n", test_sortie_2.screenB.z) ;
    printf(" (I.x %lf, I.y %lf, I.z %lf) devrait faire (0,0,0)\n", test_sortie_2.top_lefthand.x, test_sortie_2.top_lefthand.y, test_sortie_2.top_lefthand.z) ;
    */
    return(0) ;

}
