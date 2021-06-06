#ifndef BOX_H
#define BOX_H
#include "vec3.h"
#include "ray.h"

class Box
{
protected:
    //Vecteur définissants la bos sur ses axes
    Vec3 a, b;
    //epsilon pour éviter la collision avec sois même lors de la recherche d'intersection rayon box
    const double epsilon = 1.0e-5;
public:
    //Constructeur par défaut
    Box();
    //construit une box à partir de 2 vecteurs
    Box(const Vec3 &vecA,const Vec3 &vecB);
    //détecte l'intersection d'un rayon avec la box
    int Intersect(const Ray& ray,double& tmin, double& tmax ) const;
};

#endif // BOX_H
