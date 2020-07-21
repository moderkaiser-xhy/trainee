#ifndef Shape_H
#define Shape_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QVector>
#include <QMap>
#include <vector>
#include <iostream>

class Shape : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Shape(QPointF point, QObject *parent = nullptr);
    virtual ~Shape()override;
    //static QVector<QPointF> TTTT;
    QPointF getStartPoint() const;
    QPointF getEndPoint() const;

    void setStartPoint(const QPointF &point);
    void setEndPoint(const QPointF &point);
    void addLine(QGraphicsLineItem *line, bool is_first);
    QPointF center;
    void test(QGraphicsLineItem *line);
    void my_coordinate(QPointF a, QPointF b);

protected:

    QPointF start_point;  //鼠标第一次坐标；
    QPointF end_point;
    //QPointF center;
    QRectF boundingRect() const override;
    void updateCenter(const QPointF &new_pos = QPointF());

private:
    QVector<QPointF> data;
    struct Lines
    {
        QGraphicsLineItem *line;
        bool is_first;
    };
    QVector<Lines> added_lines;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void moveLinesToCenter();
};

#endif // Shape_H
