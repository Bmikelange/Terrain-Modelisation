#include "drawing.h"
#include <QRectF>

Drawing::Drawing()
{
    QPalette palette;
    col=QColor(0,0,0);
    this->setAutoFillBackground(true);
    Image=QImage(512,512,QImage::Format_ARGB32);
    Image.fill(QColor(0,0,0));
    palette.setBrush(QPalette::Background, QPixmap::fromImage(Image).scaled(this->size()));
    this->setPalette(palette);
}

void Drawing::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(col);
    std::vector<Vec2> v;
    int x=xval.getx();
    int y=xval.gety();
    for(int k=0;k<512;k++)
        for(int j=0;j<512;j++)
        {
            double dx = x - k;
            double dy = y - j;
            if(dx*dx+dy*dy<radius*radius)
                v.push_back(Vec2(k,j));
        }
    for(int j=0;j<v.size();j++)
    {
        x=v[j].getx();
        y=v[j].gety();
        painter.drawPoint(x,y);
        Image.setPixel(x,y,col.rgb());
    }

}

void Drawing::mousePressEvent(QMouseEvent *event)
{
    QPalette palette;
    xval=Vec2(event->x(),event->y());
    palette.setBrush(QPalette::Background, QPixmap::fromImage(Image).scaled(this->size()));
    this->setPalette(palette);
    repaint();
}

void Drawing::mouseMoveEvent(QMouseEvent * event)
{
    if(event != NULL )
    {
        QPalette palette;
        xval=Vec2(event->x(),event->y());
        palette.setBrush(QPalette::Background, QPixmap::fromImage(Image).scaled(this->size()));
        this->setPalette(palette);
        repaint();
    }
}

void Drawing::validate()
{
    QImage ImageTemp=Image.scaled(c.getnx(),c.getny());
    for(int i=0;i<c.getnx();i++)
        for(int j=0;j<c.getny();j++)
        {
            double b=qBlue(ImageTemp.pixel(i,j));
            double g=qGreen(ImageTemp.pixel(i,j));
            if(g==255)
                c.getSet(i,j)=1;
            else if(g==120)
                c.getSet(i,j)=2;
            else if(b==255)
                c.getSet(i,j)=3;
            else if(b==120)
                c.getSet(i,j)=4;
            else
                c.getSet(i,j)=0;
        }
}
