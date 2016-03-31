#ifndef OCTREE_H
#define OCTREE_H

#include "geometry.h"
#include "flist.h"

typedef flist**** box;


box initialize (int size_x, int size_y, int size_z, int depth, flist *facets);

int isInBox(int i, int j, int k, int depth, int size_x, int size_y, int size_z, facet* f);

#endif
