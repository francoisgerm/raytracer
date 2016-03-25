#ifndef MATRIX_H
#define MATRIX_H

#include "includes.h"

typedef struct smatrix {
        double xx;
        double xy;
        double xz;

        double yx;
        double yy;
        double yz;

        double zx;
        double zy;
        double zz;

        double det;

} matrix;

double computeDet (matrix);
matrix matProduct (matrix m, matrix n);
matrix mateDot (double k, matrix m) ;
matrix matInverse (matrix m);
#endif
