#include <stdio.h>
#include "read_entry.h"
#include "geometry.h"
#include <stdlib.h>
#include "flist.h"
#include "entry.h"
#include "next_ligne.h"
#include "is_comment.h"
#include "misc.h"
#include "intersection.h"

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
      
    int position=0;
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
		list_facet->next = NULL;

		facet* f_init = malloc(sizeof(facet));
		f_init->a.x = 0;
		f_init->a.y = 0;
		f_init->a.z = 0;

		f_init->b.x = 0;
		f_init->b.y = 0;
		f_init->b.z = 0;

		f_init->c.x = 0;
		f_init->c.y = 0;
		f_init->c.z = 0;

		list_facet->f = f_init;

//		flist* last_facet = malloc(sizeof(flist));



    color couleur;
    
    //on mesure la longueur du fichier
    fseek(file, 0, SEEK_END) ;
    int longueur = ftell(file) ;

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
        fscanf(file, "%lf",&y_0);
            fseek(file,1,SEEK_CUR); //permet de passer ","
        fscanf(file, "%lf",&z_0);
        
        //on va se placer au début de la ligne suivante
        position=next_ligne(file,position); 
        
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
        fscanf(file, "%lf",&y_a);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
        fscanf(file, "%lf",&z_a);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
        
        (sortie->screenA).x=x_a ;
        (sortie->screenA).y=y_a ;
        (sortie->screenA).z=z_a ;
        
        
        //on alloue les coordonnées du point B
        fscanf(file, "%lf", &x_b);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
        fscanf(file, "%lf",&y_b);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
        fscanf(file, "%lf",&z_b);
            fseek(file,1,SEEK_CUR); //permet de passer ", "

        (sortie->screenB).x=x_b ;
        (sortie->screenB).y=y_b ;
        (sortie->screenB).z=z_b ;
            
        //récupération de w et h
        fscanf(file, "%lf", &w);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
        fscanf(file, "%lf",&h);
            fseek(file,1,SEEK_CUR); //permet de passer ", "
        //on va se placer au début de la ligne suivante           
        position=next_ligne(file,position);

        
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
            fscanf(file,"%lf",&tmp2);
                tmpt.y=tmp2;
                fseek(file,1,SEEK_CUR); //permet de passer ", "
            fscanf(file,"%lf",&tmp3);
                tmpt.z=tmp3;
                fseek(file,1,SEEK_CUR); //permet de passer ", "
            sommets[j]=tmpt;
            position=next_ligne(file,position);        
        }
        
       
       
       //------------------
       //recherche du minimum pour décaler tous les points
       //------------------
       
       double x_min, y_min, z_min ;
       x_min=min3((sortie->screenA).x , (sortie->screenB).x , (sortie->obs).x) ;
       y_min=min3((sortie->screenA).y , (sortie->screenB).y , (sortie->obs).y) ;
       z_min=min3((sortie->screenA).z , (sortie->screenB).z , (sortie->obs).z) ;
       
       for (j=0;j<nbr_sommet;j++)
       {
            x_min =min2(x_min, sommets[j].x) ;
            y_min =min2(y_min, sommets[j].y) ;
            z_min =min2(z_min, sommets[j].z) ;
       }
       
       x_min=fabs(x_min) ;
       y_min=fabs(y_min) ;
       z_min=fabs(z_min) ;

       
       
       (sortie->obs).x +=x_min ;
       (sortie->obs).y +=y_min ;
       (sortie->obs).z +=z_min ;
       (sortie->screenA).x +=x_min ;
       (sortie->screenA).y +=y_min ;
       (sortie->screenA).z +=z_min ;
       (sortie->screenB).x +=x_min ;
       (sortie->screenB).y +=y_min ;
       (sortie->screenB).z +=z_min ;
       
       for (j=0;j<nbr_sommet;j++)
        {
            sommets[j].x +=x_min ;
            sommets[j].y +=y_min ;
            sommets[j].z +=z_min ;
        }
        
       
       
       while (is_comment(file,&position)==1)
        {
            fseek(file,0,position);
        }
        fseek(file,-1,SEEK_CUR);
        position=position-1;
       
       
       //récupération du nombre de facet
        fscanf(file,"%d",&nbr_facet);
            
        (sortie->nbFacets)=nbr_facet ;
           
        //position=next_ligne(file,position);
        //création de la liste de facet
        for(i=0;i<nbr_facet;i++)
        {
			point a;
			point b;
			point c;

    				facet* f=malloc(sizeof(facet));
            fscanf(file,"%d",&num_sommet);
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                a=(sommets[num_sommet-1]);
            fscanf(file,"%d",&num_sommet);
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                b=sommets[num_sommet-1];
            fscanf(file,"%d",&num_sommet);
                fseek(file,1,SEEK_CUR); //permet de passer ", "
                //f->c=sommets[num_sommet-1];
                c=sommets[num_sommet-1];

			*f = createFacet (a, b, c);



            fscanf(file,"%lf",&k);
                fseek(file,1,SEEK_CUR);
                f->k=k;
            fscanf(file,"%d",&l);
                fseek(file,1,SEEK_CUR);
                couleur.r=l;
            fscanf(file,"%d",&l);
                fseek(file,1,SEEK_CUR);
                couleur.g=l;
            fscanf(file,"%d",&l);
                fseek(file,1,SEEK_CUR);
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
            fseek(file,1,SEEK_CUR);
            (sortie->back).r=m;  
            
        fscanf(file,"%d",&m);
            fseek(file,1,SEEK_CUR);
            (sortie->back).g=m;     

        fscanf(file,"%d",&m);
            fseek(file,1,SEEK_CUR);
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
            fseek(file,1,SEEK_CUR);
            ((sortie->s).p).x=k + x_min;  

						printf ("%lf\n", k);
            
        fscanf(file,"%lf",&k);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).p).y=k + y_min ;     

						printf ("%lf\n", k);
        fscanf(file,"%lf",&k);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).p).z=k + z_min ;  
						printf ("%lf\n", k);
        
        
        fscanf(file,"%d",&m);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).cp).r=m; 
						printf ("%lf\n", m);
        
        fscanf(file,"%d",&m);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).cp).g=m; 
						printf ("%lf\n", m);
            
        fscanf(file,"%d",&m);
            fseek(file,1,SEEK_CUR);
            ((sortie->s).cp).b=m;  
						printf ("%lf\n", m);
        
        
  //      free(sommets);
 //       free(f);
//        free(list_facet);
        position =longueur ;
    }
    return(sortie);
    
}
