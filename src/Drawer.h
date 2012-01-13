#ifndef DRAWER_H
#define DRAWER_H

#include "QtGui"
#include <Parser.h>

class Drawer{
public:
    vector<point> scaleToScene (vector<point> result, QGraphicsScene* scene);
    void drawGridLines(QGraphicsScene* scene);
    void drawGraph(vector<point> points, QGraphicsScene* scene);
private:
    double findMax (vector<point> result);
    double findMin(vector<point> result);
};

#endif // DRAWER_H
