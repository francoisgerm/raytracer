#include "flist.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void setLast (flist *l, facet *f) {
	printf("setLast (flist*, facet*)\n");
/*
	printf ("Welcome in setLast... \n");
	flist *tmp = l;
	

	printf (" -> tmp list created...\n");

	while (tmp->next != NULL) {
//		printf ("%d -- ", tmp);
		tmp = tmp->next;
	}

	printf (" -> arrived at the end !");

	flist* new_facet = malloc (sizeof(flist)); // NOT FREED
	printf ("/!\\ unfreed memory \n");
	new_facet->next = NULL;
	tmp->next = &new_facet;
	new_facet->f = f;
}

facet* getLast (flist *l) {
	printf ("lolilol\n");
	while (l->next != NULL) {
		printf ("\n\n\n\n\n %f %f %f    |||   NAME = \n hahahamdrmdrenkuler", l->f->a.x, l->f->a.y, l->f->a.z);
		sleep(1);
		l = l->next;

	}
	printf ("lolilol bis\n");

	return l->f;
	*/
}

flist* addOnTop (flist *l, facet *f) {
//	printf ("adding on top of flist\n");

	flist* new_flist = malloc (sizeof(flist)); // NOT FREED YET !!
//	printf ("/!\\ unfreed memory in addOnTop(flist*, facet*) \n");

	new_flist->f = f;
	new_flist->next = l;


	return new_flist;

}
