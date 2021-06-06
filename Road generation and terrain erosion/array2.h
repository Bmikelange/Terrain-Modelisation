#ifndef ARRAY2_H
#define ARRAY2_H

#include "QPoint"


class Array2
{
public:
    // Tableau de points correspondants au voisin sur un cercle de rayon 1
    static const QPoint next[8];
    // Distance de ces points au point central
    static const double length[8];
    static const QPoint next2[8];
    static const QPoint next3[16];

    Array2();
};

#endif // ARRAY2_H
