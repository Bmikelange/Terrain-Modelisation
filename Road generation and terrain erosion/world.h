#ifndef WOW_H
#define WOW_H

#include "vec3.h"

class World
{
public:
    // Constructeur par defaut
    World();
    // Construit un world à partir d'un vec3
    World( const Vec3& _n ) : n(_n)
    {
        if(n.getz() < -0.9999999f)
        {
            t= Vec3(0, -1, 0);
            b= Vec3(-1, 0, 0);
        }
        else
        {
            float a= 1.f / (1.f + n.getz());
            float d= -n.getx() * n.gety() * a;
            t= Vec3(1.f - n.getx() * n.getx() * a, d, -n.getx());
            b= Vec3(d, 1.f - n.gety() * n.gety() * a, -n.gety());
        }
    }
    //passe du repère local au repère global
    Vec3 operator( ) ( const Vec3& local )  const
    {
        return local.getx() * t + local.gety() * b + local.getz() * n;
    }
    //passe du repère global au repère local
    Vec3 inverse( Vec3 global ) const { return Vec3(global * t, global * b, global* n); }

    Vec3 t;
    Vec3 b;
    Vec3 n;
};

#endif // WOW_H
