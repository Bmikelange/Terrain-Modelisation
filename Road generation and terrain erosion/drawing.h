#ifndef DRAWING_H
#define DRAWING_H

#include <QWidget>
#include <vector>
#include <QMouseEvent>
#include <vec2.h>
#include <QPainter>
#include <colorfield.h>
#include <QImage>
#include <QColor>
class Drawing : public QWidget
{
    Q_OBJECT
public:
    Drawing();
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void validate();
    void setColor(QColor col1){col=col1;}
    void setColorField(ColorField c1) { c=c1;}
    ColorField getColorField() {return c;}
    void setRadius(int r){ radius=r;}
protected :
    Vec2 xval=Vec2(0,0);
    QImage Image;
    ColorField c;
    QColor col;
    int radius=20;
};

#endif // DRAWING_H
