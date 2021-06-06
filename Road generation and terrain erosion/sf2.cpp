#include "sf2.h"


Vec2 SF2::gradient(int i, int j) const
{
    Vec2 n;
    if(i==0)
    {
        n.setx((at(i + 1,j)-at(i,j)) * InverseCellDiag.getx());
    }
    else if(i==nx-1)
    {
        n.setx((at(i,j) - at(i-1,j)) * InverseCellDiag.getx());
    }
    else
    {
        n.setx((at(i+1,j)-at(i-1,j)) * 0.5 * InverseCellDiag.getx());
    }
    if(j==0)
    {
        n.sety((at(i,j+1)-at(i,j)) * InverseCellDiag.gety());
    }
    else if(j==ny-1)
    {
        n.sety((at(i,j) - at(i,j-1)) * InverseCellDiag.gety());
    }
    else
    {
        n.sety((at(i,j+1)-at(i,j-1)) * 0.5 * InverseCellDiag.gety());
    }
    return n;
}

double SF2::laplacien(int i, int j) const
{
  double laplacian = 0.0;

  // Divergence along x axis
  if (i == 0)
  {
    laplacian += (at(i, j) - 2.0 * at(i + 1, j) + at(i + 2, j)) / (celldiagonal.getx() * celldiagonal.getx());
  }
  else if (i == nx - 1)
  {
    laplacian += (at(i, j) - 2.0 * at(i - 1, j) + at(i - 2, j)) / (celldiagonal.getx() * celldiagonal.getx());
  }
  else
  {
    laplacian += (at(i + 1, j) - 2.0 * at(i, j) + at(i - 1, j)) / (celldiagonal.getx() * celldiagonal.getx());
  }

  // Divergence along y axis
  if (j == 0)
  {
    laplacian += (at(i, j) - 2.0 * at(i, j + 1) + at(i, j + 2)) / (celldiagonal.gety() * celldiagonal.gety());
  }
  else if (j == ny - 1)
  {
    laplacian += (at(i, j) - 2.0 * at(i, j - 1) + at(i, j - 2)) / (celldiagonal.gety() * celldiagonal.gety());
  }
  else
  {
    laplacian += (at(i, j + 1) - 2.0 * at(i, j) + at(i, j - 1)) / (celldiagonal.gety() * celldiagonal.gety());
  }

  return laplacian;
}

QVector<ScalarPoint2> SF2::GetScalarPoints() const
{
  QVector<ScalarPoint2> e(nx * ny);

  int k = 0;
  for (int i = 0; i < nx; i++)
  {
    for (int j = 0; j < ny; j++)
    {
      e[k++] = ScalarPoint2(QPoint(i, j), at(i, j));
    }
  }
  return e;
}


double SF2::K() const
{
  double k = 0.0;

  for (int i = 0; i < nx; i++)
  {
    for (int j = 0; j < ny; j++)
    {
      k = std::max(k, gradient(i, j).norm());
    }
  }
  return k;
}
