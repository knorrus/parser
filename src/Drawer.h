#ifndef DRAWER_H
#define DRAWER_H

#include "QtGui"
#include <Parser.h>

class Drawer{
public:
    QVector<QPoint> scaleToScene (vector<point> result, QGraphicsScene* scene);
    void drawGridLines(QGraphicsScene* scene);
    void drawGraph(QVector<QPoint> points, QGraphicsScene* scene);
private:
    double findMax (vector<point> result);
    double findMin(vector<point> result);
};

#endif // DRAWER_H
