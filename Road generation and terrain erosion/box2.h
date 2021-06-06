#ifndef BOX2_H
#define BOX2_H

#include "vec2.h"

class Box2
{
protected:
    //Vecteurs définissant les extrémités d'une box 2D
    Vec2 a, b;
public:
    //constructeur par défaut
    Box2();
    //Construits une box à partir de 2 vecteurs 2D
    Box2(const Vec2 &vecA,const Vec2 &vecB);
    // vérifie si un vecteur est à l'intérieur de la box
    bool Inside(const Vec2 &vec) const;
    // vérifie si deux box s'intersects entre elles
    bool intersect(const Box2&) const;
};

#endif // BOX2_H
