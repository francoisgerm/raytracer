#include "../include/includes.h"

double computeDet (matrix m) {
        double det = m.xx*(m.yy*m.zz - m.zy*m.yz);
        det += m.yx * (m.xz*m.zy - m.xy*m.zz);
        det += m.zx * (m.xy*m.yz - m.xz * m.yy);

        return det;
}

matrix mateDot (double k, matrix m) {
        m.xx *= k;
        m.xy *= k;
        m.xz *= k;

        m.yx *= k;
        m.yy *= k;
        m.yz *= k;

        m.zx *= k;
        m.zy *= k;
        m.zz *= k;

        return m;
}

matrix matInverse (matrix m) {
        matrix inv;

        inv.xx = m.yy*m.zz - m.yz*m.zy;
        inv.xy = m.xy*m.zz - m.xz*m.zy;
        inv.xz = m.xy*m.yz - m.yy*m.yz;

        inv.yx = m.yx*m.zz - m.yz*m.zx;
        inv.yy = m.xx*m.zz - m.xz*m.zx;
        inv.yz = m.xx*m.yz - m.yx*m.xz;

        inv.zx = m.yx*m.zy - m.zx*m.yy;
        inv.zy = m.xx*m.zy - m.zx*m.xy;
        inv.zz = m.xx*m.yy - m.xy*m.yx;


        return mateDot(1.0/computeDet(m), inv);
}

matrix matProduct (matrix m, matrix n) {
        matrix result;

        result.xx = m.xx * n.xx + m.xy * n.yx + m.xz * n.zx;
        result.xy = m.xx * n.xy + m.xy * n.yy + m.xz * n.zy;
        result.xz = m.xx * n.xz + m.xy * n.yz + m.xz * n.zz;

        result.yx = m.yx * n.xx + m.yy * n.yx + m.yz * n.zx;
        result.yy = m.yx * n.xy + m.yy * n.yy + m.yz * n.zy;
        result.yz = m.yx * n.xz + m.yy * n.yz + m.yz * n.zz;

        result.zx = m.zx * n.xx + m.zy * n.yx + m.zz * n.zx;
        result.zy = m.zx * n.xy + m.zy * n.yy + m.zz * n.zy;
        result.zz = m.zx * n.xz + m.zy * n.yz + m.zz * n.zz;


        return result;
}
