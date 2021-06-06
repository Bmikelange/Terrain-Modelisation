#include "grid2.h"

bool Grid2::Inside(int i, int j) const
{
    return ((i>= 0) && (i< nx) && (j>=0) && (j< ny));
}
bool Grid2::Border(int i , int j) const
{
    return ((i== 0) || (i == nx-1) || (j==0) || (j == ny-1));
}
int Grid2::index(int i, int j) const
{
    return i + j * nx;
}
Vec2 Grid2::Vertex(int i, int j) const
{
    double u=double(i)/(nx-1);
    double v=double(j)/(ny-1);
    return Vec2((1-u) * a.getx() +u*b.getx(), (1-v)  * a.gety()+v*b.gety());

}
