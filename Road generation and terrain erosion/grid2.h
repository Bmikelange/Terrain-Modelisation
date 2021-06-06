#ifndef GRID2_H
#define GRID2_H
#include "box2.h"

class Grid2: public Box2
{
protected:
    //dimensions de la grille
    int nx,ny;
    //diagonale de la grille
    Vec2 diagonal;
    // Diagonale pour une cellule
    Vec2 celldiagonal;
    // inverse de celldiagonal
    Vec2 InverseCellDiag;
public:
    //constructeur par défaut
    Grid2(){}
    // Construit une grille à partir d'une box et de ses dimensions
    Grid2(const Box2& box, int nx, int ny):Box2(box),nx(nx),ny(ny)
    {
        diagonal = b-a;
        celldiagonal = diagonal.Scale(1.0 / double(nx - 1), 1.0 / double(ny - 1));
        InverseCellDiag = Vec2(1.0/celldiagonal.getx(), 1.0/celldiagonal.gety());
    }
    // Vérifie si l'on est à l'intérieur de la grille
    bool Inside(int i, int j) const;
    // Vérifie si l'on est sur les bords de la grille
    bool Border(int i , int j) const;
    // Transforme les indices de parcours d'un tableau 2D en un indice de parcours pour un tableau 1D
    int index(int i, int j) const;
    //
    Vec2 Vertex(int i, int j) const;
    // récupère la taille en x de la grille
    int getnx(){return nx;}
    // récupère la taille en y de la grille
    int getny(){return ny;}
};

#endif // GRID2_H
