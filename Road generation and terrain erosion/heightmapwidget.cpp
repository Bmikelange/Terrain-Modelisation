#include <GL/glew.h>
#include "heightmapwidget.h"
#include "QWheelEvent"
#include "QMouseEvent"
#include "QImageReader"
#include "QDebug"

void HeightMapWidget::setImg(Image ims)
{
    img=ims;
}

void HeightMapWidget::reset()
{
    road.resize(0);
}

void HeightMapWidget::setTexture(Image ims)
{
    texture=ims;
}

void HeightMapWidget::initializeGL()
{
    m_vertices.resize(0);
    m_color.resize(0);
    vertices_by_x=img.width();
    vertices_by_y=img.height();

    glClearColor(1.0, 1.0, 1.0, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    QVector3D  vertice;
    int scale=1.0;

    double max=std::max(img.max(),1.0);

    for(int y=0;y<vertices_by_y-2;y++)
    {
        for(int x=0;x<vertices_by_x-2;x++)
        {
            double color=img.pixel(x,y).getx();
            vertice.setX(Xpas*((double)x/vertices_by_x)-0.5);
            vertice.setY(scale*(double)qGray(color)/max);
            vertice.setZ(Ypas*((double)y/vertices_by_y)-0.5);
            m_vertices.push_back(vertice);
            Vec3 col=texture.pixel(x,y);
            m_color.push_back(QVector3D(col.getx()/255.0,col.gety()/255.0,col.getz()/255.0));
            color=img.pixel(x,y+1).getx();
            vertice.setX(Xpas*((double)x/vertices_by_x)-0.5);
            vertice.setY(scale*(double)qGray(color)/max);
            vertice.setZ(Ypas*((double)(y+Ypas)/vertices_by_y)-0.5);
            m_vertices.push_back(vertice);
            col=texture.pixel(x,y+1);
            m_color.push_back(QVector3D(col.getx()/255.0,col.gety()/255.0,col.getz()/255.0));
            color=img.pixel(x+1,y).getx();
            vertice.setX(Xpas*((double)(x+Xpas)/vertices_by_x)-0.5);
            vertice.setY(scale*(double)qGray(color)/max);
            vertice.setZ(Ypas*((double)y/vertices_by_y)-0.5);
            col=texture.pixel(x+1,y);
            m_color.push_back(QVector3D(col.getx()/255.0,col.gety()/255.0,col.getz()/255.0));
            m_vertices.push_back(vertice);
            color=img.pixel(x+1,y+1).getx();
            vertice.setX(Xpas*((double)(x+Xpas)/vertices_by_x)-0.5);
            vertice.setY(scale*(double)qGray(color)/max);
            vertice.setZ(Ypas*((double)(y+Ypas)/vertices_by_y)-0.5);
            m_vertices.push_back(vertice);
            col=texture.pixel(x+1,y+1);
            m_color.push_back(QVector3D(col.getx()/255.0,col.gety()/255.0,col.getz()/255.0));
        }

    }

}

void HeightMapWidget::setPas(int x,int y)
{
    Xpas=x;
    Ypas=y;
}

void HeightMapWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,-distance,-distance,0.0,0.0,0.0,0.0,1.0,0.0);
    glRotatef(xRot/16.0f,1.0f,0.0f,0.0f);
    glRotatef(yRot/16.0f,0.0f,1.0f,0.0f);
    glRotatef(zRot/16.0f,0.0f,0.0f,1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f,1.0*width()/height(),0.1f,100.0f);
    for(int i=0;i<m_vertices.size();i+=4)
    {
        glBegin(GL_TRIANGLES);
        glColor3d(m_color[i].x(),m_color[i].y(),m_color[i].z());
        glVertex3f(m_vertices[i].x(),m_vertices[i].y(),m_vertices[i].z());
        glColor3d(m_color[i+1].x(),m_color[i+1].y(),m_color[i+1].z());
        glVertex3f(m_vertices[i+1].x(),m_vertices[i+1].y(),m_vertices[i+1].z());
        glColor3d(m_color[i+2].x(),m_color[i+2].y(),m_color[i+2].z());
        glVertex3f(m_vertices[i+2].x(),m_vertices[i+2].y(),m_vertices[i+2].z());
        glEnd();
        glBegin(GL_TRIANGLES);
        glColor3d(m_color[i+2].x(),m_color[i+2].y(),m_color[i+2].z());
        glVertex3f(m_vertices[i+2].x(),m_vertices[i+2].y(),m_vertices[i+2].z());
        glColor3d(m_color[i+3].x(),m_color[i+3].y(),m_color[i+3].z());
        glVertex3f(m_vertices[i+3].x(),m_vertices[i+3].y(),m_vertices[i+3].z());
        glColor3d(m_color[i+1].x(),m_color[i+1].y(),m_color[i+1].z());
        glVertex3f(m_vertices[i+1].x(),m_vertices[i+1].y(),m_vertices[i+1].z());
        glEnd();
    }
    for(int i=0;i<(int)road.size()-1;i++)
    {
        glBegin(GL_LINES);
        glColor3d(500,0,0);
        glVertex3f(road[i].getx(),road[i].gety(),road[i].getz());
        glVertex3f(road[i+1].getx(),road[i+1].gety(),road[i+1].getz());
        glEnd();
    }
}

void HeightMapWidget::resizeGL(int w, int h){

}

void HeightMapWidget::wheelEvent(QWheelEvent *event)
{
    distance*=1.0+1.0 * event->delta()/1200.0;
}

void HeightMapWidget::mousePressEvent(QMouseEvent * event)
{
       last_pos=event->pos();
}

void HeightMapWidget::mouseMoveEvent(QMouseEvent * event)
{
    int dx=event->x() -last_pos.x();
    int dy=event->y() - last_pos.y();
    if(event != NULL )
    {
        rotate(dy*8,0,0);
        rotate(0,dx*8,0);
        update();
    }
    last_pos=event->pos();
}
void HeightMapWidget::rotate(int x,int y,int z)
{
    xRot +=x;
    yRot+=y;
    zRot += z;
}

void HeightMapWidget::setRoad(std::vector<std::pair<int,int>> p)
{
    road.resize(0);
    for(unsigned int i=0;i<p.size();i++)
    {
        double x=img.pixel(p[i].first,p[i].second).getx();
        double max=std::max(img.max(),1.0);
        double vx=Xpas*((double)p[i].first/vertices_by_x)-0.5;
        double vy=Ypas*((double)p[i].second/vertices_by_y)-0.5;
        road.push_back(Vec3(vx,((double)qGray(x)+1)/max,vy));
    }
}
