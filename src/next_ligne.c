#include <stdio.h>
#include "read_entry.h"
#include <stdlib.h>


int next_ligne(FILE* file, int position)
{
    //permet de passer à la ligne suivante
    char mem;
    int end_ligne=position;
   

    fseek(file,0,position); //on se place au début de la ligne (à la position "position")
    fscanf(file,"%c",&mem);
    end_ligne++ ;
    //printf("%d %c \n",end_ligne, mem) ;

	while (mem!='\n')
    {
        //tant que l'on n'a pas atteint la fin de la ligne
        fscanf(file,"%c",&mem);
        //printf("%d %c \n", end_ligne, mem);
        end_ligne++ ;
    }
    //printf("nouvelle position dans le fichier %d \n", end_ligne);
    return(end_ligne) ;

//use fgets,  suppose lire une ligne
//essayer avec gets
// char chaine[longueur] ="";
//FILE*fichier=NULL
//fichier=fopen()
//fgets(chaine,longueur,fichier)

}
