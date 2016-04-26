#ifndef MOVERAY_H
#define MOVERAY_H

#include <stdlib.h>

#include "geometry.h"
#include "flist.h"
#include "intersection.h"
#include "misc.h"
#include "divisions.h"

facet* nextIntersection (settings s, ray r);
//facet* moveRay (box space, settings s, ray r);
//ray moveRayToNextBox (ray r, settings s);
//flist* getPotFacets (box space, settings s, ray r);
//double nextBoxT (settings s, ray r);
//double getStep (settings s, ray r);

//int* boxesInPath (settings s, ray r);

#endif
