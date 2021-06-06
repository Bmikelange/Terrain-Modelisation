#include "vec2.h"

Vec2::Vec2()
{
    x=0;
    y=0;
}

Vec2 Vec2::operator+(const Vec2 &v)
{
    Vec2 result = Vec2(x+v.getx(),y+v.gety());
    return result;
}

Vec2 Vec2::operator-(const Vec2 &v)
{
    Vec2 result = Vec2(x-v.getx(),y-v.gety());
    return result;
}
Vec2 Vec2::operator-()
{
    return Vec2(-x,-y);
}

double Vec2::operator*(const Vec2 &v)
{
    return x*v.getx() + y*v.gety();
}

Vec2 Vec2::Scale(double a, double b)
{
    Vec2 result = Vec2(x*a,y*b);
    return result;
}
