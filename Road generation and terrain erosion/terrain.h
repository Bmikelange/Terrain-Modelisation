#ifndef TERRAIN_H
#define TERRAIN_H

#include <QImage>
#include <QString>

class Terrain
{
protected :
    //image lue
    QImage img;
public:
    // Constructeur par défaut
    Terrain();
    // Lis l'image depuis le disque dur
    void setImg(std::string s)
    {
        if(!s.empty())
        {
            img.load(QString::fromStdString(s));
        }
    }
    // Return img
    QImage getimg()
    {
        return img;
    }
    // non implémenté -> TODO
    void setImgBruit(int sizex, int sizey);
};

#endif // TERRAIN_H
