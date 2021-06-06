#include "box2.h"

Box2::Box2()
{
}

Box2::Box2(const Vec2 &vecA,const Vec2 &vecB)
{
    a = vecA;
    b = vecB;
}

bool Box2::Inside(const Vec2 &vec) const
{
    return (a.getx()<=vec.getx() && a.gety()<=vec.gety() && b.getx()>=vec.getx() && b.gety()>=vec.gety());
}

bool Box2::intersect(const Box2 &box) const
{
    if (a.getx() >= box.b.getx() || a.gety()>=box.b.gety() || b.getx()<=box.a.getx() || b.gety()<=box.a.gety())
        return false;
    else
        return true;
}
