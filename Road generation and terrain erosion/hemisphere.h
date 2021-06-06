#ifndef HEMISPHERE_H
#define HEMISPHERE_H
#include "vec3.h"
#include "random.h"



class Hemisphere
{
public:
    //constructeur par défaut
    Hemisphere();
    //génère des points aléatoires sur une hemisphère
    static Vec3 RandomDirection( Vec3& axis, Random& random);
};

#endif // HEMISPHERE_H
