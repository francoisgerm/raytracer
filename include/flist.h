#ifndef FLIST_H
#define FLIST_H

#include "geometry.h"

struct sflist {
	struct sflist* next;
	facet* f;
};

typedef struct sflist flist;

void setLast (flist *l, facet *f);
facet* getLast (flist *l);

flist* addOnTop (flist *l, facet *f) ;
#endif
