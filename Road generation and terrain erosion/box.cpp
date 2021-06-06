#include "box.h"

Box::Box()
{

}

Box::Box(const Vec3 &vecA,const Vec3 &vecB)
{
    a = vecA;
    b = vecB;
}

int Box::Intersect(const Ray& ray, double& tmin, double& tmax) const
{
  tmin = -1e16;
  tmax = 1e16;

  Vec3 p = ray.Origin();
  Vec3 d = ray.Direction();

  double t;
  // Ox
  if (d.getx() < -epsilon)
  {
    t = (a.getx() - p.getx()) / d.getx();
    if (t < tmin)
      return 0;
    if (t <= tmax)
      tmax = t;
    t = (b.getx() - p.getx()) / d.getx();
    if (t >= tmin)
    {
      if (t > tmax)
        return 0;
      tmin = t;
    }
  }
  else if (d.getx() > epsilon)
  {
    t = (b.getx() - p.getx()) / d.getx();
    if (t < tmin)
      return 0;
    if (t <= tmax)
      tmax = t;
    t = (a.getx() - p.getx()) / d.getx();
    if (t >= tmin)
    {
      if (t > tmax)
        return 0;
      tmin = t;
    }
  }
  else if (p.getx()<a.getx() || p.getx()>b.getx())
    return 0;

  // Oy
  if (d.gety() < -epsilon)
  {
    t = (a.gety() - p.gety()) / d.gety();
    if (t < tmin)
      return 0;
    if (t <= tmax)
      tmax = t;
    t = (b.gety() - p.gety()) / d.gety();
    if (t >= tmin)
    {
      if (t > tmax)
        return 0;
      tmin = t;
    }
  }
  else if (d.gety() > epsilon)
  {
    t = (b.gety() - p.gety()) / d.gety();
    if (t < tmin)
      return 0;
    if (t <= tmax)
      tmax = t;
    t = (a.gety() - p.gety()) / d.gety();
    if (t >= tmin)
    {
      if (t > tmax)
        return 0;
      tmin = t;
    }
  }
  else if (p.gety()<a.gety() || p.gety()>b.gety())
    return 0;

  // Oz
  if (d.getz() < -epsilon)
  {
    t = (a.getz() - p.getz()) / d.getz();
    if (t < tmin)
      return 0;
    if (t <= tmax)
      tmax = t;
    t = (b.getz() - p.getz()) / d.getz();
    if (t >= tmin)
    {
      if (t > tmax)
        return 0;
      tmin = t;
    }
  }
  else if (d.getz() > epsilon)
  {
    t = (b.getz() - p.getz()) / d.getz();
    if (t < tmin)
      return 0;
    if (t <= tmax)
      tmax = t;
    t = (a.getz() - p.getz()) / d.getz();
    if (t >= tmin)
    {
      if (t > tmax)
        return 0;
      tmin = t;
    }
  }
  else if (p.getz()<a.getz() || p.getz()>b.getz())
    return 0;

  return 1;
}
