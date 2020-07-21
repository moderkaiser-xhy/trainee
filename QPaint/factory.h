#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "shape.h"
#include "star.h"

class Factory
{
public:
    virtual Shape* createShape(const QPointF &point) = 0;
    virtual ~Factory();
};

class StarFactory : public Factory
{
public:
    Shape* createShape(const QPointF &point) override;
};

#endif // FACTORY_HPP
