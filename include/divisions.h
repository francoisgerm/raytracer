#ifndef OCTREE_H
#define OCTREE_H

#include "geometry.h"
#include "flist.h"
#include "misc.h"

typedef flist**** box;
typedef flist* subBox;


box initialize (settings s);

int isInBox(int i, int j, int k, int depth, int size_x, int size_y, int size_z, facet* f);

int* getBoxId (settings s, ray r) ;

int sameBox (int *b1, int* b2);
#endif
