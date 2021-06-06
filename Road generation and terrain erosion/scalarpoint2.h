#ifndef SCALARALPHA2_H
#define SCALARALPHA2_H

#include <QPoint>

class ScalarPoint2
{
protected:
  QPoint p; // Point de coordonnée i j
  double z; // Hauteur associée
public:
  //Constructeur par défaut
  ScalarPoint2() {}
  // Constuit le ScalarPoint à partir d'un point et d'une hauteur
  ScalarPoint2(const QPoint& p, const double& s) :p(p), z(s) {}
  // surcharge l'opérateur pour comparer deux ScalarPoint
  friend bool operator<(const ScalarPoint2& a, const ScalarPoint2& b) { return a.z < b.z; }

  // Accès au membre de la fonction
  QPoint Point() const {return p;}
  double Scalar() const{return z;}
};

#endif // SCALARALPHA2_H
