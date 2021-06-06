#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <vec3.h>
#include <assert.h>


class Image
{
protected:
    // une image
    std::vector<std::vector<Vec3>> image;
    //dimensions de l'image
    int nx,ny;
public:
    //constructeur par défaut
    Image();
    // Construit une image de dimensions _nx, _ny
    Image(int _nx,int _ny):nx(_nx),ny(_ny){
        image.resize(nx);
        for(int i=0;i<nx;i++)
        {
            image[i].resize(ny,Vec3(0.0,0.0,0.0));
        }
    }
    // additionne deux images ensemble
    static Image addImage(Image A, Image B)
    {
        assert(A.width()==B.width() && A.height()==B.height());
        Image result(A.width(),A.height());
        for(int i=0;i<A.width();i++)
            for(int j=0;j<A.height();j++)
                result.setPixel(i,j,A.pixel(i,j)+B.pixel(i,j));
        double max=result.max();
        for(int i=0;i<A.width();i++)
            for(int j=0;j<A.height();j++)
            {
                Vec3 x=result.pixel(i,j);
                double r=(x.getx()/max) *255;
                double g=(x.gety()/max) *255;
                double b=(x.getz()/max) *255;
                result.setPixel(i,j,Vec3(r,g,b));
            }
        return result;

    }
    // set la valeur du pixel i j à N
    void setPixel(int i,int j,Vec3 N){
        image[i][j]=N;
    }
    // récupère la valeur du pixel i j
    Vec3 pixel(int i,int j)
    {
        return image[i][j];
    }
    // récupère la dimension x de l'image
    int width(){return nx;}
    // récupère la dimension y de l'image
    int height(){return ny;}
    //calcule la valeur maximale sur l'image
    double max()
    {
        double max=0;
        for(int i=0;i<nx;i++)
        {
            double val=0;
            for(int j=0;j<nx;j++)
            {
                int temp=image[i][j].getx();
                if(temp<image[i][j].gety())
                    temp=image[i][j].gety();
                if(temp<image[i][j].getz())
                    temp=image[i][j].getz();
                if(val<temp)
                {
                    val=temp;
                }
            }
            if(val>max)
                max=val;
        }
        return max;
    }
};

#endif // IMAGE_H
