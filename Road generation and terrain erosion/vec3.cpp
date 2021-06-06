#include "vec3.h"

Vec3::Vec3()
{
    x=0;
    y=0;
    z=0;
}

Vec3 Vec3::operator+(const Vec3 &v)
{
    Vec3 result = Vec3(x+v.getx(),y+v.gety(),z+v.getz());
    return result;
}

Vec3 Vec3::plus(Vec3 v) const
{
    Vec3 result = Vec3(x+v.getx(),y+v.gety(),z+v.getz());
    return result;
}

Vec3 Vec3::operator-(const Vec3 &v)
{
    Vec3 result = Vec3(x-v.getx(),y-v.gety(),z-v.getz());
    return result;
}

double Vec3::operator*(const Vec3 &v)
{
 return x*v.getx() + y*v.gety() + z*v.getz();
}

Vec3 Vec3::Scale(double a, double b, double c)
{
    Vec3 result = Vec3(x*a,y*b,z*c);
    return result;
}

Vec3 Vec3::operator-()
{
    return Vec3(-x,-y,-z);
}
