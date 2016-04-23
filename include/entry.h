#ifndef ENTRY_H
#define ENTRY_H

#include "geometry.h"

typedef struct sentry{
    color back;
    int width, height, nbPoints, nbFacets;
    point obs, screenA, screenB;
    flist* Facets ;
    source s;
} entry;


#endif
