#ifndef HEIGHTMAPWIDGET_H
#define HEIGHTMAPWIDGET_H

#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QVector>
#include <image.h>


class HeightMapWidget : public QOpenGLWidget
{
Q_OBJECT
public:
    //Construit le widget
    HeightMapWidget(QWidget * parent):QOpenGLWidget(parent){}
    // initialise le mesh et la texture à afficher et set les paramètres OpenGL
    void initializeGL() override;
    // Dessine le mesh
    void paintGL() override;
    // resize l'affichage
    void resizeGL(int w, int h) override;
    // zoom ou dézoome sur le mesh
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent * event) override;
    //tourne autour du mesh
    void mouseMoveEvent(QMouseEvent * event) override;
    //calcule les rotations autour du mesh
    void rotate(int x,int y,int z);
    //Définis l'image utilisée pour générer le mesh
    void setImg(Image ims);
    //Définis le pas utilisé pour générer le mesh
    void setPas(int x, int y);
    //renvoie le pas selon l'axe x
    int getPasx(){return Xpas;}
    //renvoie le pas selon l'axe y
    int getPasy(){return Ypas;}
    //Définis la texture utilisée sur le mesh
    void setTexture(Image ims);
    //Récupère la texture du mesh
    Image getTexture(){return texture;}

    void setRoad(std::vector<std::pair<int,int>> p);
    void reset();

private:
    //Contient l'ensemble des triangles du mesh
    QVector<QVector3D> m_vertices;
    //Contient l'ensemble des couleurs associées à chaque point du mesh
    QVector<QVector3D> m_color;
    //nombre de vertex en x
    int vertices_by_x;
    //nombre de vertex en y
    int vertices_by_y;
    //Image de base pour générer le mesh
    Image img;
    //Image de Texture
    Image texture;
    //distance d'affichage (positionne la caméra)
    double distance=-1.0;
    // rotation de la caméra en x
    double xRot=0;
    // rotation de la caméra en y
    double yRot=0;
    // rotation de la caméra en z
    double zRot=0;
    // dernière position de la souris
    QPoint last_pos;

    // pas pour dessiner en x
    int Xpas=1;
    // pas pour dessiner en y
    int Ypas=1;

    std::vector<Vec3> road;
};

#endif // HEIGHTMAPWIDGET_H
