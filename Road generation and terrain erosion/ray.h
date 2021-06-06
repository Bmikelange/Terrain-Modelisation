#ifndef RAY_H
#define RAY_H
#include <vec3.h>

class Ray
{
protected:
  //origine du rayon
  Vec3 o;
  //direction du rayon
  Vec3 d;
public:
    // constructeur par défaut
    Ray();
    //construit un rayon avec son origine et sa direction
    Ray(Vec3 _o,Vec3 _d):o(_o),d(_d){}
    //renvoie l'origine du rayon
    Vec3 Origin() const
    {
        return o;
    }
    //renvoie la destination du rayon
    Vec3 Direction() const {
            return d;
    }
    //récupère le point du rayon qui à touché un objet
    Vec3 operator()(double t) const
    {
      return o.plus(t * d);
    }
};

#endif // RAY_H
