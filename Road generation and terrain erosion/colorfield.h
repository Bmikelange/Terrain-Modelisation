#ifndef COLORFIELD_H
#define COLORFIELD_H

#include <vec3.h>
#include <vector>
#include <QImage>
#include <image.h>
#include <cmath>
#include "hf.h"

class ColorField
{
protected:
    // contient les valeurs de hauteur pour chaque point
    std::vector<int> field;
    int nx, ny;

public:
    //constructeur par défaut
    ColorField();

    ColorField(int x, int y) {
        nx=x;
        ny=y;
        field.resize(x*y,0);
    }

    int index(int i ,int j) const
    {
        return i + j * nx;
    }

    // récupère en lecture la valeur stockée aux coordonnées i,j
    int at(int i, int j) const {
        return field.at(index(i, j));
    }
    // récupère en lecture et écriture la valeur stockée aux coordonnées i,j
    int& getSet(int i, int j) {
        return field.at(index(i, j));
    }

    // récupère en lecture la valeur stockée aux coordonnées i,j
    int at(int i) const {
        return field.at(i);
    }

    int getnx(){return nx;}
    int getny(){return ny;}
    // récupère en lecture et écriture la valeur stockée aux coordonnées i,j
    int& getSet(int i) {
        return field.at(i);
    }

    void setValue()
    {
        for(float i=0;i<nx;i++)
        {
            for(float j=0;j<ny;j++)
            {
                field[index(i,j)]=0;

            }
        }
    }

    void setHF(HF & h)
    {
        for(int i=0;i<nx;i++)
        {
            for(int j=0;j<ny;j++)
            {
                int n=at(i,j);
                if(n==5)
                    h.getSet(i,j)=h.at(i,j)+20;
            }
        }
    }

    std::vector<int> getfield(){ return field;}

    Image getTexture(){
        Image image(nx,ny);
        for(int i=0;i<nx;i++)
        {
            for(int j=0;j<ny;j++)
            {

                int n=at(i,j);
                if(n==1)
                    image.setPixel(i,j,Vec3(0,255,0));
                else if(n==2)
                    image.setPixel(i,j,Vec3(0,120,0));
                else if(n==3)
                    image.setPixel(i,j,Vec3(0,0,255));
                else if(n==4)
                    image.setPixel(i,j,Vec3(0,0,120));
                else if(n==5)
                    image.setPixel(i,j,Vec3(255,0,0));
                else
                    image.setPixel(i,j,Vec3(0,0,0));
            }
        }

       return image;
    }
};

#endif // COLORFIELD_H
