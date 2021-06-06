#ifndef HF_H
#define HF_H


#include "sf2.h"
#include "vec3.h"
#include <math.h>
#include <image.h>
#include "ray.h"
#include "box.h"
#include "QImage"


class HF : public SF2
{
protected :

    // Texture en sortie
    Image Texture;
    // Carte des hauteurs calculées
    Image HeightMap;
    // rapport taille image/taille grille en x
    float Xpas=1;
    // rapport taille image/taille grille en y
    float Ypas=1;

public:
    // constructeur par défaut
    HF(){}
    // Construit un Heightfield à partir d'un scalarfield
    HF(const SF2& s) : SF2(s){}
    //renvoie la hauteur en i j du terrain
    double height(int i, int j) const {return at(i,j);}
    // calcule la pente en un point du terrain
    double slope(int i, int j) const {Vec2 g=gradient(i,j); return sqrt(g*g);}
    // calcule la moyenne des différence des pentes autour d'un point
    double averageSlope(int i, int j) const;
    // renvoie le veteur contenant i, j et la hauteur associée
    Vec3 vertex(int i, int j) const {return Vec3(Grid2::Vertex(i,j),height(i,j));}
    // renvoie la normal au point i j
    Vec3 Normal(int i, int j) const;
    //Rempli la texture avec les informations de hauteur
    void RHeight();
    //Rempli la texture avec les informations de normal
    void RNormal();
    //Rempli la texture avec un blinn
    void RBlin();
    //Rempli la texture avec les informations de pentes
    void RSlope();
    //Rempli la texture avec les informations de pentes moyenne
    void RASlope();
    //Rempli la texture avec les informations sur le laplacien en chaque point
    void RLaplacien();
    //Rempli la texture avec les informations de courant
    void RSArea(float intensity);
    //calcule la carte des hauteurs de l'image
    void computeHeightMap();
    //Rempli le field avec les bonnes hauteurs depuis une image
    void setfield(QImage img);
    // récupère la texture calculée précedemment
    Image getTexture(){return Texture;}
    // récupère la carte des hauteurs calculée précédemment
    Image getHeightMap(){return HeightMap;}
    // récupère le pas en X
    int getXpas(){return Xpas;}
    //récupère le pas en Y
    int getYpas(){return Ypas;}
    // Calcule les chemins probables emprunté par de l'eau dans la direction de la pente la plus forte
    SF2 StreamAreaSteepest() const;
    // Calcule les chemins probables emprunté par de l'eau en répartissant les valeurs dans les 8 directions autour du point en fonction de sa pente
    SF2 StreamArea() const;
    // Calcule les endroits ou le courant est le plus fort (plus la pente est élevée)
    SF2 StreamPower(SF2 streamArea);
    // Calcule les endroits ou l'eau va stagner (plus la pente est faible)
    SF2 WetnessIndex(SF2 streamArea);
    // Errode le terrain en fonction du streamPower
    SF2 StreamPowerErode(SF2 streamArea, double k);
    // Errode le terrain en fonction de son laplacien
    SF2 Hill_Slope(double k);
    // Estime l'éclairage ambiant de la scène
    SF2 Access();
    //Calcul un ScalarField de pente
    SF2 SSlope();
    //Calcul un ScalarField de pente moyenne
    SF2 SASlope();
    //Calcul un ScalarField de laplacien
    SF2 SLaplacien();
    //Utilisation de l'algorithme de depression_filling de richdem
    SF2 SRichdem_depression_filling();
    //Utilisation de l'algorithme de depression_breaching de richdem
    SF2 SRichdem_depression_breaching();
    //génère la texture pour l'erosion selon le stream power
    void RSSPE(float intensity);
    //génère la texture pour l'erosion selon le hill slope
    void RSHLE(float intensity);
    //génère la texture pour l'accessibilité
    void RSAccess();
    //
    int CheckFlowSlope(const QPoint& p, QPoint* point, double* height, double* slope, double* nslope, int& mask) const;
    //calcule l'intersection entre un rayon et le terrain
    bool intersect(const Ray& ray,double& t, Vec3& q, const Box& box,const double& k,const double& length) const;
    // vérifie si on est à l'intérieur de la grille (encore)
    bool InsideVertexIndex(int i, int j) const
    {
      return (i >= 0) && (i < nx) && (j >= 0) && (j < ny);
    }
};

#endif // HF_H
