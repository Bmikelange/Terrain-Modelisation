#include "array2.h"
#include <math.h>


const QPoint Array2::next[8] = { QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1), QPoint(-1, 0), QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1) };
const double Array2::length[8] = { 1.0, sqrt(2.0), 1.0, sqrt(2.0), 1.0, sqrt(2.0), 1.0, sqrt(2.0) };
const QPoint Array2::next2[8] = { QPoint(-2, -1), QPoint(-2, 1), QPoint(-1, 2), QPoint(1, 2), QPoint(2, 1), QPoint(2, -1), QPoint(1, -2), QPoint(-1, -2) };
const QPoint Array2::next3[16] = { QPoint(-3, -2),QPoint(-3, -1), QPoint(-3, 1),QPoint(-3, 2), QPoint(-2, -3),QPoint(-1, -3), QPoint(1, -3),QPoint(2, -3), QPoint(3, -2),QPoint(3, -1), QPoint(3, 1),QPoint(3, 2), QPoint(2, 3),QPoint(1, 3), QPoint(-1, 3),QPoint(-2, 3) };


Array2::Array2()
{
}
