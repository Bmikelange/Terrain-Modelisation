#include "export.h"
#include <QImage>
#include <QString>
#include <fstream>
#include <QDebug>

Export::Export()
{

}

void Export::ExportTexture(Image img)
{
    QImage image(img.width(),img.height(), QImage::Format_ARGB32);
    for(int i=0;i<img.width();i++)
    for(int j=0;j<img.height();j++)
    {
        Vec3 v=img.pixel(i,j);
        QColor rgb =QColor(v.getx(),v.gety(),v.getz(),1.0);
        image.setPixel(i,j,rgb.rgb());
    }
    image.save(QString::fromStdString("../mmv_tp2/Export/sortie.jpg"));
}

void Export::ExportMesh(HF heightfield, int Xpas, int Ypas)
{
    std::ofstream file;
    std::vector<Vec3> vec;
    file.open("../mmv_tp2/Export/terrain.obj");
    file << "o terrain" << std::endl;
    for(int i=0;i<heightfield.getnx()-1;i++)
        for(int j=0;j<heightfield.getny()-1;j++)
        {
            int ny=heightfield.getny();
            vec.push_back(Vec3(i*ny+j,i*ny+j+1,(i+1)*ny+j));
            vec.push_back(Vec3(i*ny+j+1,(i+1)*ny+j+1,(i+1)*ny+j));
        }
    for(int i=0;i<heightfield.getnx();i++)
        for(int j=0;j<heightfield.getny();j++)
        {
            file << "v " << Xpas*((double)i/heightfield.getnx()) <<" "<< (double)qGray(std::max(0.0,heightfield.at(i,j)))/255 <<" "<< Ypas*((double)j/heightfield.getny())  << std::endl;
        }
    for(int i=0;i<heightfield.getnx();i++)
        for(int j=0;j<heightfield.getny();j++)
        {
            Vec3 n=heightfield.Normal(i,j);
            file << "vn " << n.getx() <<" "<< n.gety() <<" "<< n.getz() << std::endl;
        }
    file<<"s off";
    for(unsigned int i=0;i<vec.size();i++)
        file << "f " << vec[i].getx()+1 <<"//"<<vec[i].getx()+1<<" "<< vec[i].gety()+1 <<"//"<<vec[i].gety()+1<<" "<< vec[i].getz()+1 <<"//"<<vec[i].getz()+1<< std::endl;
    file.close();
}
