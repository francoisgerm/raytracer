#include "read_entry.h"
#include "next_ligne.h"
#include "is_comment.h"
#include "flist.h"
#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>

//gcc ./src/next_ligne.c ./src/is_comment.c ./src/read_entry.c ./src/flist.c ./test_read.c -Iinclude 


int main()
{
    entry* list_facet=malloc(sizeof(flist));
    //int new_position ;
    //char mem1;
    //int com ;
    
    //ligne nécessaires pour le test de next_ligne et is_comment
    
    /*FILE* file ;
    file = fopen("./src/read/test.scn","r") ;
    if (file==NULL) 
        {
        printf("le fichier n'est pas lu \n");
        return(-1);
        } */
        
                    //test next_ligne
    //new_position = next_ligne(file,0);
    //printf("la nouvelle posision est %d \n", new_position);
    
    
                //test is_comment
    //com= is_comment(file,25);
    //printf("doit retourner 1 : %d \n", com);
    
                //test read_entry
    //z=read("./src/read/test.scn") ;
    list_facet=read("./scenes/cubes.scn");
    free(list_facet);
    return (0) ;
}
