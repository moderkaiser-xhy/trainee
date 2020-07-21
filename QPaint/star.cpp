#include "star.h"
#include <math.h>
#include<iostream>


Star::Star(QPointF point) : Shape(point)
{
    Q_UNUSED(point)
}



void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon star;
    qreal x1=getStartPoint().x();
    qreal y1=getStartPoint().y();
    qreal x2=getEndPoint().x();
    qreal y2=getEndPoint().y();

    if(abs(x1-x2)>10){
        star << QPoint(x1,y1)
             << QPoint(x1,y1+20)
             << QPoint(x1+20,y1+20)
             << QPoint(x1+20,y1);

        painter->setPen(Qt::black);
        painter->drawPolygon(star);
    }
    std::cout<<x1 << " " ;

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
