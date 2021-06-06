#ifndef VEC2_H
#define VEC2_H
#include <math.h>


class Vec2
{
private:
    //coordonnées du vecteur
    double x,y;
public:
    //constructeur
    Vec2();
    //construit un vecteur à partir de deux coordonnées
    Vec2(double _x, double _y){x=_x;y=_y;}
    //additionne deux vecteurs
    Vec2 operator+(const Vec2 &vec);
    //soustrait deux vecteurs
    Vec2 operator-(const Vec2 &vec);
    // renvoie l'inverse du vecteur
    Vec2 operator-();
    // renvoie le produit scalaire entre deux vecteurs
    double operator*(const Vec2 &vec);
    // multiplie un vecteur par un Scalaire
    friend Vec2 operator*(double a,const Vec2 &vec){return Vec2(a*vec.getx(),a*vec.gety());}
    //récupère la coordonnée x du vecteur
    double getx()const {return x;}
    //récupère la coordonnée y du vecteur
    double gety()const {return y;}
    //set la coordonnée x du vecteur
    void setx(const double& _x ) {x=_x;}
    //set la coordonnée y du vecteur
    void sety(const double& _y ) {y=_y;}
    //Scale le vecteur en x et y
    Vec2 Scale(double a, double b);
    //renvoie la norme du vecteur
    double norm(){return std::sqrt(x*x+y*y);}
};

#endif // VEC2_H
