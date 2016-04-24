#ifndef DISPLAY_H
#define DISPLAY_H

#include "geometry.h"
#include "moveRay.h"
#include "misc.h"

#include <stdio.h>

color getPixelColor (int x, int y, settings s, box space);
color getRayColor (ray r, settings s, box space, int refl);
#endif
