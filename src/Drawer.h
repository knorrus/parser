#ifndef DRAWER_H
#define DRAWER_H

#include "QtGui"

class Drawer {
public:
    void drawGridLines(QGraphicsScene* scene);
    void drawGraph(QVector<QPoint> points, QGraphicsScene* scene);
};

#endif // DRAWER_H
