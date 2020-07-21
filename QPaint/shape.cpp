#include "shape.h"
#include <iostream>
using namespace std;

QVector<QPointF> TTTT;
Shape::Shape(QPointF point, QObject *parent) :
            QGraphicsObject()
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
    Q_UNUSED(parent)
}

Shape::~Shape()
{

}

void Shape::setStartPoint(const QPointF &point)
{
    start_point = point;
}

void Shape::setEndPoint(const QPointF &point)
{
    end_point = point;
    updateCenter();
}

QPointF Shape::getStartPoint() const
{
    return start_point;
}

QPointF Shape::getEndPoint() const
{
    return end_point;
}

QRectF Shape::boundingRect() const
{
    qreal x1=getStartPoint().x();
    qreal y1=getStartPoint().y();
    return QRectF(x1,y1,20,20);
}

void Shape::updateCenter(const QPointF &new_pos)
{
    qreal x_offset = boundingRect().x() + boundingRect().width()/2;
    qreal y_offset = boundingRect().y() + boundingRect().height()/2;
    this->center = QPointF(new_pos.x() + x_offset, new_pos.y() + y_offset);

}

void Shape::addLine(QGraphicsLineItem *line, bool is_first)
{
    if(is_first)
        line->setLine(QLineF(center, line->line().p2()));
    else
        line->setLine(QLineF(line->line().p1(), center));
    added_lines.push_back({line, is_first});
}
void Shape::test(QGraphicsLineItem *abcd){
    abcd->setLine(QLineF(10,10,100,100));
    added_lines.push_back({abcd, true});
}

void Shape::my_coordinate(QPointF a, QPointF b){
    if(!TTTT.size()){
        TTTT.push_back(a);
        return;
    }
    int sig=-1;
    for(int i=0; i<TTTT.size(); ++i){
        if(TTTT[i] == b){
            sig=i;
            break;
        }
    }
    if(sig==-1) TTTT.push_back(a);
    else TTTT[sig]=center;
    cout << TTTT.size() <<endl;
    return;
}




QVariant Shape::itemChange(GraphicsItemChange change, const QVariant &value)
{

    if (change == ItemPositionChange && scene())
    {
        QPointF center_sig=center;

        QPointF new_pos = value.toPointF();
        updateCenter(new_pos);

        my_coordinate(center, center_sig);
        moveLinesToCenter();

    }
    return QGraphicsItem::itemChange(change, value);
}

void Shape::moveLinesToCenter()
{
    if(!added_lines.isEmpty())
    {
        for (auto &line : added_lines)
        {
            //std::cout << added_lines.size() << endl;
            if(line.is_first){
                line.line->setLine(QLineF(center, line.line->line().p2()));
                //cout << line.line->line().p2().x() << " ";
                //cout << line.line->line().p2().y() <<endl;
            }
            else
                line.line->setLine(QLineF(line.line->line().p1(), center));

        }
    }
}
