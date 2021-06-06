#ifndef SF2_H
#define SF2_H

#include "grid2.h"
#include "vec3.h"
#include <vector>
#include <QImage>
#include "scalarpoint2.h"
#include <utility>


class SF2 : public Grid2
{
protected:
    // contient les valeurs de hauteur pour chaque point
    std::vector<double> field;

public:
    //constructeur par défaut
    SF2() {}
    // définis le scalarfield à partir d'une grille et d'une valeur
    SF2(const Grid2 grid,double h): Grid2(grid){
        field.resize(nx*ny,h);
    }
    //définis le scalarfield à partir d'une grille
    SF2(const Grid2 grid): Grid2(grid){
        field.resize(nx*ny,0.0);
    }
    // récupère en lecture la valeur stockée aux coordonnées i,j
    double at(int i, int j) const {
        return field.at(index(i, j));
    }
    // récupère en lecture et écriture la valeur stockée aux coordonnées i,j
    double& getSet(int i, int j) {
        return field.at(index(i, j));
    }
    //tableau 1d vers 2d
    std::pair<int,int> transform(int i) const {
        double x=(double)i/nx;
        int jresult=x;
        double v=(x-jresult);
        int iresult=v*nx;
        return std::pair<int, int>(iresult,jresult);
    }

    //calcul le gradient en un point du field
    Vec2 gradient(int i, int j) const;
    //calcul le laplacien en un point du field
    double laplacien(int i, int j) const;
    //renvoie l'ensemble des scalar point associés à un point de la grille
    QVector<ScalarPoint2> GetScalarPoints() const;
    //renvoie la constante de lipschitz associée à la grille
    double K() const;
    // renvoie la Box2 associée au scalarfield
    Box2 GetBox() const
    {
      return Box2(a, b);
    }
    //renvoie la valeur maximale de la sf2
    double max(){return *std::max_element(field.begin(),field.end());}
};

#endif // SF2_H
