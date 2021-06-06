#include "random.h"

Random::Random()
{

}

Vec3 Random::aleatory()
{
    float r1=(rand()%10000/10000.f);
    float r2=(rand()%10000/10000.f);
    float x=std::cos(2*M_PI*r1)*std::sqrt(1-r2*r2);
    float y=std::sin(2*M_PI*r1)*std::sqrt(1-r2*r2);
    float z=r2;
    return Vec3(x,y,z);

}
