#ifndef VEC3_H
#define VEC3_H

#include<vec2.h>
#include<math.h>

class Vec3
{
private:
    //coordonnées du vecteur
    double x, y, z;
public:
    //constructeur
    Vec3();
    //construit un vecteur à partir de trois coordonnées
    Vec3(double _x, double _y, double _z){x=_x;y=_y;z=_z;};
    //construit un vecteur à partir d'un vec2 et de deux coordonnées
    Vec3(Vec2 v, double _z){x=v.getx();y=v.gety();z=_z;};
    //additionne deux vecteurs
    Vec3 operator+(const Vec3 &vec);
    //additionne deux vecteurs
    Vec3 plus(Vec3 vec) const;
    //fais le produit scalaire entre deux vecteurs
    double operator*(const Vec3 &vec);
    // multiplie un vecteur par un Scalaire
    friend Vec3 operator*(double a,const Vec3 &vec){return Vec3(a*vec.getx(),a*vec.gety(),a*vec.getz());}
    // soustrait deux vecteurs
    Vec3 operator-(const Vec3 &vec);
    // renvoie la coordonnée x du vecteur
    double getx()const {return x;};
    // renvoie la coordonnée y du vecteur
    double gety()const {return y;};
    // renvoie la coordonnée z du vecteur
    double getz()const {return z;};
    // set la coordonnée x du vecteur
    void setx(const double& _x ) {x=_x;}
    // set la coordonnée y du vecteur
    void sety(const double& _y ) {y=_y;}
    // set la coordonnée z du vecteur
    void setz(const double& _z ) {z=_z;}
    //Scale le vecteur selon ses trois coordonnées
    Vec3 Scale(double a, double b, double c);
    // calcule la longueur du vecteur
    double length(){return sqrt(x*x+y*y+z*z);}
    // normalise un vecteur
    Vec3 normalize(){
        double l=length();
        return Vec3(x/l,y/l,z/l);
    }
    //renvoie l'inverse du vecteur
    Vec3 operator-();
    // effectue une interpolation bilineaire entre 4 vecteurs
    static Vec3 Bilinear(const Vec3& a00, const Vec3& a10, const Vec3& a11, const Vec3& a01, const double& u, const double& v)
    {
      return (1 - u) * (1 - v) * a00 + (1 - u) * (v)* a01 + (u)* (1 - v) * a10 + (u)* (v)* a11;
    }
};

#endif // VEC3_H
