#include <stdio.h>
#include "read_entry.h"
#include "geometry.h"
#include <stdlib.h>
#include "flist.h"
#include "entry.h"
#include "next_ligne.h"
#include "is_comment.h"

//avoir le nombre de facet total
//translater l'ensemble des points !!!!!!


entry* read ( char* filename)
{
    //ouverture du fichier et vérification qu'il s'ouvre
    FILE* file ;
    file = fopen(filename,"r") ;
    if (file==NULL) 
        return(NULL);
    
    entry* sortie=malloc(sizeof(entry)) ;
      
    //char mem ;
    int position=0;
    //char test;  a supprimer à la fin!!!!!!!!!!
    double x_0, y_0, z_0;
    double x_a, y_a, z_a;
    double x_b, y_b, z_b;
    double w,h ;
    int nbr_sommet,nbr_facet, num_sommet;
    int j,i;
    double k;
    int l,m;
    point* sommets ;
    flist* list_facet=malloc(sizeof(flist));
    facet* f=malloc(sizeof(facet));
    color couleur;
    
    //on mesure la longueur du fichier
    fseek(file, 0, SEEK_END) ;
    int longueur = ftell(file) ;
    printf("longueur %d \n", longueur) ;

    //on se place de nouveau au début
    fseek(file,0, SEEK_SET) ;    
    
    //on parcourt le fichier
    while(position<longueur) 
    {
       
       
       
        while (is_comment(file,&position)==1)
        {
           fseek(file,0,position);
        }
        //on recule d'un le premier char ayant été lu par is_comment         
        fseek(file,-1,SEEK_CUR);
        position=position-1;
        
        //on alloue les coordonnées de l'observateur
        //la position ne nous intéresse pas sur cette ligne    
        fscanf(file, "%lf", &x_0);
            fseek(file,1,SEEK_CUR); //permet de passer ","
            printf("%lf x_0 \n", x_0);
        fscanf(file, "%lf",&y_0);
            fseek(file,1,SEEK_CUR); //permet de passer ","
            printf("%lf y_0 \n", y_0) ;
        fscanf(file, "%lf",&z_0);
            printf("%lf z_0 \n", z_0);
        
        //on va se placer au début de la ligne suivante
        position=next_ligne(file,position); 
        printf("\n");
        
        (sortie->obs).x=x_0 ;
        (sortie->obs).y=y_0 ;
        (sortie->obs).z=z_0 ;
        
        
        
        
        while (is_comment(file,&position)==1)
        {
            fseek(file,0,position);
        }
        fseek(file,-1,SEEK_CUR);
        position=position-1;
        
        //on alloue les coordonnées du point A    
        fscanf(file, "%lf", &x_a);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
            printf("%lf x_a \n", x_a);
        fscanf(file, "%lf",&y_a);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
            printf("%lf y_a \n", y_a) ;
        fscanf(file, "%lf",&z_a);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
            printf("%lf z_a \n", z_a);
        
        (sortie->screenA).x=x_a ;
        (sortie->screenA).y=y_a ;
        (sortie->screenA).z=z_a ;
        
        
        //on alloue les coordonnées du point B
        fscanf(file, "%lf", &x_b);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
            printf("%lf x_b \n", x_b);
        fscanf(file, "%lf",&y_b);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
            printf("%lf y_b \n", y_b) ;
        fscanf(file, "%lf",&z_b);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
            printf("%lf z_b \n", z_b);

        (sortie->screenB).x=x_b ;
        (sortie->screenB).y=y_b ;
        (sortie->screenB).z=z_b ;
            
        //récupération de w et h
        fscanf(file, "%lf", &w);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
            printf("%lf w \n",w);
        fscanf(file, "%lf",&h);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
            printf("%lf h \n", h) ; 
        //on va se placer au début de la ligne suivante           
        position=next_ligne(file,position);

        printf("\n");
        
        (sortie->width)=w ;
        (sortie->height)=h ;




        while (is_comment(file,&position)==1)
        {
            fseek(file,0,position);
        }
        fseek(file,-1,SEEK_CUR);
        position=position-1;
        
        //récupération du nombre de sommet
        fscanf(file,"%d",&nbr_sommet);
            printf("%d nbr_sommet \n", nbr_sommet) ;
        position=next_ligne(file,position);

        (sortie->nbPoints)=nbr_sommet;
        
        //création du tableau contenant les sommmets
        double tmp1,tmp2,tmp3;
        point tmpt ;
        sommets=malloc(nbr_sommet*sizeof(point));
        
        for (j=0;j<nbr_sommet;j++)
        {
            tmpt=sommets[j];
            
            fscanf(file,"%lf",&tmp1);
                tmpt.x=tmp1;
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                //printf("sommet %d x %lf  ", j, sommets[j].x ) ;
            fscanf(file,"%lf",&tmp2);
                tmpt.y=tmp2;
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                //printf("sommet %d y %lf  ", j, sommets[j].y ) ;
            fscanf(file,"%lf",&tmp3);
                tmpt.z=tmp3;
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                //printf("sommet %d z %lf \n", j, sommets[j].z ) ;
            sommets[j]=tmpt;
            printf("sommet %d x %lf  ", j, sommets[j].x ) ;
            printf("sommet %d y %lf  ", j, sommets[j].y ) ;
            printf("sommet %d z %lf \n", j, sommets[j].z ) ;
            position=next_ligne(file,position);        
        }
        
       
       while (is_comment(file,&position)==1)
        {
            fseek(file,0,position);
        }
        fseek(file,-1,SEEK_CUR);
        position=position-1;
       
       
       //récupération du nombre de facet
        fscanf(file,"%d",&nbr_facet);
            printf("%d nbr_facet \n", nbr_facet) ;
            
        (sortie->nbFacets)=nbr_facet ;
           
        //position=next_ligne(file,position);
        //création de la liste de facet
        for(i=0;i<nbr_facet;i++)
        {
            fscanf(file,"%d",&num_sommet);
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                printf("num_sommet %d  ", num_sommet);
                (f->a)=(sommets[num_sommet-1]);
            fscanf(file,"%d",&num_sommet);
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                printf("num_sommet %d  ", num_sommet);
                f->b=sommets[num_sommet-1];
            fscanf(file,"%d",&num_sommet);
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                printf("num_sommet %d  ", num_sommet);
                f->c=sommets[num_sommet-1];
            fscanf(file,"%lf",&k);
                fseek(file,1,SEEK_CUR);
                printf("coeff reflexion %lf  ",k);
                f->k=k;
            fscanf(file,"%d",&l);
                fseek(file,1,SEEK_CUR);
                printf("r %d  ",l);
                couleur.r=l;
            fscanf(file,"%d",&l);
                fseek(file,1,SEEK_CUR);
                printf("g %d  ",l);
                couleur.g=l;
            fscanf(file,"%d",&l);
                fseek(file,1,SEEK_CUR);
                printf("b %d \n",l);
                couleur.b=l;
            f->cp=couleur;
                                
            list_facet=addOnTop(list_facet, f);
        }      

        (sortie->Facets)=malloc(sizeof(flist));
        (sortie->Facets)=list_facet ;
        
        position=next_ligne(file,position);
        
        
        
        
        while (is_comment(file,&position)==1)
        {
            fseek(file,0,position);
        }
        fseek(file,-1,SEEK_CUR);
        position=position-1;
        
        //lecture de la couleur du background
        fscanf(file,"%d",&m);
            printf("r %d  ",m);
            fseek(file,1,SEEK_CUR);
            (sortie->back).r=m;  
            
        fscanf(file,"%d",&m);
            fseek(file,1,SEEK_CUR);
            printf("g %d  ",m);
            (sortie->back).g=m;     

        fscanf(file,"%d",&m);
            fseek(file,1,SEEK_CUR);
            printf("b %d  \n",m);
            (sortie->back).b=m;  
    
        position=next_ligne(file,position);
  
  
        
        while (is_comment(file,&position)==1)
        {
            fseek(file,0,position);
        }
        fseek(file,-1,SEEK_CUR);
        position=position-1;
        
        //lecture des cactéristiques de la source
        fscanf(file,"%lf",&k);
            printf("x %lf  ",k);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).p).x=k;  
            
        fscanf(file,"%lf",&k);
            fseek(file,1,SEEK_CUR);
            printf("y %lf  ",k);
            ((sortie->s).p).y=k;     

        fscanf(file,"%lf",&k);
            fseek(file,1,SEEK_CUR);
            printf("z %lf ",k);
            ((sortie->s).p).z=k;  
        
        
        fscanf(file,"%d",&m);
            printf("r %d  ",m);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).cp).r=m; 
        
        fscanf(file,"%d",&m);
            printf("g %d  ",m);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).cp).g=m; 
            
        fscanf(file,"%d",&m);
            printf("b %d  ",m);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).cp).b=m;  
        
        
        free(sommets);
        free(f);
        free(list_facet);
        position =longueur ;
        printf("test \n");  
    }
    return(sortie);
    
}
