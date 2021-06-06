#include "hemisphere.h"
#include "world.h"

Hemisphere::Hemisphere()
{

}

Vec3 Hemisphere::RandomDirection(Vec3& axis , Random& random)
{
  Vec3 d = random.aleatory();
  World w(axis);
  w(d);
  return d;
}
