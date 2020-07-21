#include "paintdesk.h"
#include<iostream>
using namespace std;

PaintDesk::PaintDesk(QObject *parent) :
                    QGraphicsScene(parent),
                    mode(PaintDesk::NoMode),
                    first_touch(QPointF()),
                    temp_Shape(nullptr),
                    line(nullptr),
                    sides_of_Polygon(QList<QGraphicsLineItem *>())
{
    QPointF abc(50,10);
    for(int i=0; i<2; ++i){
        mymymy(new test(abc));
    }

    //mymymy(new test(abc));
}

PaintDesk::~PaintDesk()
{

}

PaintDesk::Mode PaintDesk::getMode() const
{
    return mode;
}

void PaintDesk::setMode(const PaintDesk::Mode mode)
{
    this->mode = mode;
    setFirstTouchIsNull();
}

void PaintDesk::setFirstTouchIsNull()
{
    this->first_touch = QPointF();
}

void PaintDesk::mymymy(Shape *temp_Shape =nullptr){
    this->temp_Shape = temp_Shape;
    QPointF abc(10,10);
    this->temp_Shape->setPos(abc);
    this->addItem(this->temp_Shape);
    this->temp_Shape->setFlags(QGraphicsItem::ItemIsMovable);
    this->temp_Shape->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);

}
void PaintDesk::addShapeToDesk(QGraphicsSceneMouseEvent *event = nullptr,
                              Shape *temp_Shape = nullptr)
{
    if(event != nullptr && temp_Shape != nullptr)
    {
        this->temp_Shape = temp_Shape;
        this->temp_Shape->setPos(event->pos());
    }
    this->addItem(this->temp_Shape);
    this->temp_Shape->setFlags(QGraphicsItem::ItemIsMovable);
    this->temp_Shape->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void PaintDesk::uniteShapesWithLine(const QPointF &second_touch)
{
    Shape  *first_Shape = dynamic_cast<Shape *>(QGraphicsScene::items(first_touch).first());
    Shape  *second_Shape = dynamic_cast<Shape *>(QGraphicsScene::items(second_touch).first());
    if(first_Shape && second_Shape){
        //QPointF P1= first_Shape->center;
        //QPointF P2= second_Shape->center;
        //this->line = this->addLine(QLineF(P1, P2));

        this->line = QGraphicsScene::addLine(QLineF (first_touch.x(), first_touch.y(),second_touch.x(), second_touch.y()));

        first_Shape->addLine(line, true);

        second_Shape->addLine(line, false);
        setFirstTouchIsNull();
    }
    setFirstTouchIsNull();
}

void PaintDesk::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (mode)
    {
        case NoMode:
        {
            QGraphicsScene::mousePressEvent(event);
            break;
        }
        case UnitMode:
        {
            if (!(this->items(event->scenePos()).isEmpty()))
            {
                if (first_touch.isNull())
                    first_touch = event->scenePos();
                else if (this->items(first_touch).first() != this->items(event->scenePos()).first())
                    uniteShapesWithLine(event->scenePos());
            }
            break;
        }
        case StarMode:
        {
            addShapeToDesk(event, new Star(event->scenePos()));
            break;
        }



    }
}

void PaintDesk::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (mode)
    {
        case NoMode:
        {
            QGraphicsScene::mouseMoveEvent(event);
            break;
        }
        case UnitMode:
            break;
        default:
        {
            temp_Shape->setEndPoint(event->scenePos());
            this->update();
            break;
        }
    }
}

void PaintDesk::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
}
