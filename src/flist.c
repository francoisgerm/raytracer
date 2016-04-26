#include "flist.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void setLast (flist *l, facet *f) {
	printf("setLast (flist*, facet*)\n");
}

flist* addOnTop (flist *l, facet *f) {
	flist* new_flist = malloc (sizeof(flist)); // NOT FREED YET !!

	new_flist->f = f;
	new_flist->next = l;


	return new_flist;
}
