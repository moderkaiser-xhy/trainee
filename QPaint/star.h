#ifndef STAR_H
#define STAR_H

#include "shape.h"
#include <cmath>

class Star : public Shape
{
    Q_OBJECT

public:
    explicit Star(QPointF point);

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // STAR_H
