#include "hf.h"
#include "array2.h"
#include <QDebug>
#include <random.h>
#include <hemisphere.h>
#include <richdem/common/Array2D.hpp>
#include <richdem/depressions/depressions.hpp>
#include <Utility.h>

Vec3 HF::Normal(int i, int j) const
{
    return Vec3(-gradient(i,j),1.0).normalize();
}

double HF::averageSlope(int i, int j) const
{
    double s=0.0;
    double x=slope(i,j);
    for(int mi=-1;mi<2;mi++)
    {
        for(int ni=-1;ni<2;ni++)
        {
            if(i+mi>=0 && j+ni>0 && i+mi<nx && j+ni<ny)
                s+=slope(i+mi,j+ni)-x;
        }
    }
    return s/8;
}


double moy_Point(QImage img, int i,int j)
{
    int count=0;
    double result=qBlue(img.pixel(i,j));
    count++;
    if(i-1>=0 && j-1>=0)
    {
        result+=qBlue(img.pixel(i-1,j-1));
        count++;
    }
    if(i-1>=0)
    {
        result+=qBlue(img.pixel(i-1,j));
        count++;
    }
    if(i-1>=0 && j+1<img.height())
    {
        result+=qBlue(img.pixel(i-1,j+1));
        count++;
    }
    if(j-1>=0)
    {
        result+=qBlue(img.pixel(i,j-1));
        count++;
    }
    if(j+1<img.height())
    {
        result+=qBlue(img.pixel(i,j+1));
        count++;
    }
    if(i+1<img.width() && j-1>=0)
    {
        result+=qBlue(img.pixel(i+1,j-1));
        count++;
    }
    if(i+1<img.width())
    {
        result+=qBlue(img.pixel(i+1,j));
        count++;
    }
    if(i+1<img.width() && j+1<img.height())
    {
        result+=qBlue(img.pixel(i+1,j+1));
        count++;
    }
    return result/count;
}

void HF::setfield(QImage img)
{
    Xpas=(double)img.width()/nx;
    Ypas=(double)img.height()/ny;
    for(float i=0;i<img.width();i+=Xpas)
    {
        for(float j=0;j<img.height();j+=Ypas)
        {

            int i2=std::min(round(i/Xpas),(float)nx-1);
            int j2=std::min(round(j/Ypas),(float)ny-1);
            int i3=i;
            int j3=j;
            float moy=(i-i3+j-j3)/2;
            double n=moy_Point(img,i3,j3);
            Vec3 v1=Vec3(n,n,n);
            if(i3+1<img.height())
                n=moy_Point(img,i3+1,j3);
            Vec3 v2=Vec3(n,n,n);
            if(j3+1<img.width())
                n=moy_Point(img,i3,j3+1);
            Vec3 v3=Vec3(n,n,n);
            if(j3+1<img.width() && i3+1<img.height())
                n=moy_Point(img,i3+1,j3+1);
            Vec3 v4=Vec3(n,n,n);
            field[index(i2,j2)]=(double)Vec3::Bilinear(v1,v2,v3,v4,1-moy,moy).getx();
        }
    }
}


void HF::RHeight()
{
    Image image(nx,ny);
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            float n=std::max(0.0,at(i,j));
            Vec3 N(n,n,n);
            image.setPixel(i,j,N);
        }
    }

   Texture=image;
}

void HF::RSArea(float intensity)
{
    double max=*std::max_element(field.begin(),field.end());
    double min=*std::min_element(field.begin(),field.end());
    Image image(nx,ny);
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            double n=at(i,j);
            Vec3 N(Utility::clamp(intensity * std::sqrt((n-min)/(max-min)),0,1)*255,0,0);
            image.setPixel(i,j,N);
        }
    }

   Texture=image;
}

void HF::RSAccess()
{
    double max=*std::max_element(field.begin(),field.end());
    double min=*std::min_element(field.begin(),field.end());
    Image image(nx,ny);
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            double n=at(i,j);
            Vec3 N(n*255,0,(1-n)*255);
            image.setPixel(i,j,N);
        }
    }

   Texture=image;
}

void HF::RSSPE(float intensity)
{
    double max=*std::max_element(field.begin(),field.end());
    double min=*std::min_element(field.begin(),field.end());
    Image image(nx,ny);
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            double n=at(i,j);
            double result=Utility::clamp(intensity * std::sqrt((n-min)/(max-min)),0,1)*255*0.9;
            Vec3 N(result,result,result);
            image.setPixel(i,j,N);
        }
    }

   Texture=image;
}

void HF::RSHLE(float intensity)
{
    double max=*std::max_element(field.begin(),field.end());
    double min=*std::min_element(field.begin(),field.end());
    Image image(nx,ny);
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            double n=at(i,j);
            double result=Utility::clamp(intensity * std::sqrt((n-min)/(max-min)),0,1)*255*0.9;
            Vec3 N(result,result,result);
            image.setPixel(i,j,N);
        }
    }

   Texture=image;
}

void HF::RNormal()
{
    Image image(nx,ny);
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            Vec3 N=Normal(i,j);
            float r=Utility::clamp((0.5+N.getx()*5),0.0,1.0)*255.0;
            float g=Utility::clamp((0.5+N.gety()*5),0.0,1.0)*255.0;
            float b=N.getz()*255.0;
            Vec3 result(r,g,b);
            image.setPixel(i,j,result);
        }
    }

   Texture=image;
}

void HF::RSlope()
{
    Image image(nx,ny);
    std::vector<double> Slope;
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            Slope.push_back(pow(slope(i,j),0.33));
        }
    }
    double max=*std::max_element(Slope.begin(),Slope.end());
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            double N=Slope[i*ny+j]/max;
            N=Utility::clamp(N,0.0,1.0);
            unsigned int r = N * 255;
            unsigned int b = (1.0 - N) * 255;
            Vec3 result(r,0,b);
            image.setPixel(i,j,result);
        }
    }
   Texture=image;
}

void HF::RASlope()
{
    Image image(nx,ny);
    std::vector<double> Slope;
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            Slope.push_back(pow(fabs(averageSlope(i,j)),0.33));
        }
    }
    double max=*std::max_element(Slope.begin(),Slope.end());
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            double N=Slope[i*ny+j]/max;
            N=Utility::clamp(N,0.0,1.0);
            unsigned int r = N * 255;
            unsigned int b = (1.0 - N) * 255;
            Vec3 result(r,0,b);
            image.setPixel(i,j,result);
        }
    }
    Texture=image;
}

void HF::RLaplacien()
{
    Image image(nx,ny);
    std::vector<double> Slope;
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            Slope.push_back(pow(fabs(laplacien(i,j)),0.33));
        }
    }
    double max=*std::max_element(Slope.begin(),Slope.end());
    double min=*std::min_element(Slope.begin(),Slope.end());
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            double N=(Slope[i*ny+j]-min)/(max-min);
            N=Utility::clamp(N,0.0,1.0);
            unsigned int r = N * 255;
            unsigned int b = (1.0 - N) * 255;
            Vec3 result(r,0,b);
            image.setPixel(i,j,result);
        }
    }
   Texture=image;
}

void HF::RBlin()
{
    Image image(nx, ny);
    const Vec3 lightdir(Vec3(100.0,100.0,250.0).normalize());

    for(int j = 0; j < ny; j++)
    for(int i = 0; i < nx; i++)
    {
        Vec3 n = Normal(i,j);
        double d = n*lightdir;
        d = (1.0+d) / 2.0;
        d *= d;
        d *= 255;
        Vec3 color( d, d, d);
        image.setPixel( i, j,color);
    }

    Texture=image;
}

void HF::computeHeightMap()
{
    Image image(nx,ny);
    double maximum=max();
    for(int i=0;i<nx;i++)
    {
        for(int j=0;j<ny;j++)
        {
            float n=std::max(0.0,at(i,j));
            Vec3 N(n,n,n);
            image.setPixel(i,j,N);
        }
    }
    HeightMap=image;
}


int HF::CheckFlowSlope(const QPoint& p, QPoint* point, double* height, double* slope, double* nslope, int& mask) const {
    int n = 0;
    double zp = at(p.x(),p.y());
    double slopesum = 0.0;
    mask = 0;
    for (int i = 0; i < 8; i++) {
        QPoint b = p + Array2::next[i];
        if (!InsideVertexIndex(b.x(), b.y())) {
            continue; }
        double step = at(b.x(),b.y()) - zp;
        if (step < 0.0) {
            point[n] = b;
            height[n] = -step;
            slope[n] = -step / Array2::length[i];
            slopesum += slope[n];
            n++;
            mask |= 1 << i; }
    }
    for (int k = 0; k < n; k++) {
        nslope[k] = slope[k] / slopesum;
    }
    return n;
}

SF2 HF::StreamArea() const
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    QVector<ScalarPoint2> QEE = GetScalarPoints();
    std::sort(QEE.begin(),QEE.end());
    for(int i=QEE.size()-1;i>=0;i--)
    {
        QPoint p=QEE.at(i).Point();
        QPoint q[8];
        double h[8];
        double s[8];
        double sn[8];
        int m;
        int n=CheckFlowSlope(p,q,h,s,sn,m);
        if(n>0)
        {
            const double sp = stream.at(p.x(),p.y());
            for(int j=0;j<n;j++)
            {
                stream.getSet(q[j].x(),q[j].y()) +=sp * sn[j];
            }
        }
    }
    return stream;

}

SF2 HF::StreamAreaSteepest() const
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    QVector<ScalarPoint2> QEE = GetScalarPoints();
    std::sort(QEE.begin(),QEE.end());
    for(int i=QEE.size()-1;i>=0;i--)
    {
        QPoint p=QEE.at(i).Point();
        QPoint q[8];
        double h[8];
        double s[8];
        double sn[8];
        int m;
        int n=CheckFlowSlope(p,q,h,s,sn,m);
        if(n>0)
        {
            double ss= s[0];
            int k=0;
            for(int j=1; j <n; j++)
            {
                if(s[j]>ss)
                {
                    k=j;
                    ss=s[j];
                }
            }
            const double sp = stream.at(p.x(),p.y());
            stream.getSet(q[k].x(),q[k].y()) +=sp;
        }
    }
    return stream;
}

SF2 HF::StreamPower(SF2 streamArea)
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
            stream.getSet(i,j)=sqrt(streamArea.at(i,j))*slope(i,j);
    return stream;
}

SF2 HF::StreamPowerErode(SF2 streamArea,double k)
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    //double maximum=max();
    //double k=2.244*u/maximum;
    //ici u=0;
    // en vrai nous devrions prendre u constant et k=2.244*u/maximum mais pour simplifier l'affichage nous faisons comme ceci.
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
        {
            double s=slope(i,j);
            double A=sqrt(streamArea.at(i,j));
            double x=at(i,j)+25000*(-k*A*s);
            stream.getSet(i,j)=x;
        }
    return stream;
}

SF2 HF::Hill_Slope(double k)
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
            stream.getSet(i,j)=at(i,j)+250000*(k*laplacien(i,j));
    return stream;
}


SF2 HF::SRichdem_depression_filling()
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    richdem::Array2D<double> a(field.data(),nx,ny);
    richdem::FillDepressions<richdem::Topology::D8,double>(a);
    double * t=a.data();
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
            stream.getSet(i,j)=t[i+j*nx];
    return stream;
}


SF2 HF::SRichdem_depression_breaching()
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    richdem::Array2D<double> a(field.data(),nx,ny);
    richdem::BreachDepressions<richdem::Topology::D8,double>(a);
    double * t=a.data();
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
            stream.getSet(i,j)=t[i+j*nx];
    return stream;
}

SF2 HF::WetnessIndex(SF2 streamArea)
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
            stream.getSet(i,j)=log(streamArea.at(i,j))/(slope(i,j)+0.1);
    return stream;
}

SF2 HF::SSlope()
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
            stream.getSet(i,j)=slope(i,j);
    return stream;
}

SF2 HF::SASlope()
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
            stream.getSet(i,j)=averageSlope(i,j);
    return stream;
}

SF2 HF::SLaplacien()
{
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
            stream.getSet(i,j)=laplacien(i,j);
    return stream;
}

bool HF::intersect(const Ray& ray,double& t, Vec3& q, const Box& box,const double& k,const double& length) const
{
    double ta,tb;
    if(!box.Intersect(ray,ta,tb)) return false;
    if(ta<-1.0e8 ||tb>+1.0e8) return false;

    tb=std::min(tb, length);
    t=std::max(ta +0.0001,0.0);
    while(t<tb)
    {
        Vec3 p=ray(t);
        double z = height(std::min(round(p.getx()),(double)nx-1),std::min(round(p.gety()),(double)ny-1));
        double h=p.getz()-z;
        if(h<0.0001)
        {
            q=Vec3(p.getx(),p.gety(),z);
            return true;
        }
        else {
            t += std::max(h/k,0.0001);
        }
    }
    return false;
}

SF2 HF::Access()
{
    int n=256;
    double r=1;
    double epsilon=0.05;
    double lipchitz=K();
    Box box=Box(Vec3(a,-1000),Vec3(b,1000));
    SF2 stream(Grid2(Box2(a,b), nx, ny),1.0);
    Random random;
    for(int i=0;i<nx;i++)
        for(int j=0;j<ny;j++)
        {
            Vec3 p=vertex(i,j)+Vec3(0,0,epsilon);
            Vec3 normal=Normal(i,j);
            int hit=0;
            for(int k=0;k<n;k++)
            {
                Vec3 direction = Hemisphere::RandomDirection(normal, random);
                Ray ray(p,p+direction);
                double t;
                Vec3 q;
                if(intersect(ray,t,q,box,lipchitz,r))
                {
                    hit++;
                }
            }
            stream.getSet(i,j)=1.0-double(hit)/double(n);
        }
    return stream;
}
