#include <stdio.h>
#include "read_entry.h"
#include "next_ligne.h"
#include "is_comment.h"
#include <stdlib.h>

int is_comment(FILE* file, int *position)
{
    //regarde si la ligne est un commentaire ou non
    //position indique le début de la ligne
    //1=comment ; else=non_comment
    char mem;
    int sortie=0; // indique si c'est un commentaire ou non
    
    fseek(file,0, *position) ; //on se place à position
    fscanf(file,"%c",&mem); //on lit le premier char de la ligne
    //printf(" premier char %c \n", mem);
	if ('#'==mem) 
        {
		*position=next_ligne(file,*position);
        sortie=1 ;
        //printf(" position nouvelle ligne %d \n", *position) ;
        }
    //printf("la nouvelle position est: %d \n", *position);
    return(sortie) ;
}
