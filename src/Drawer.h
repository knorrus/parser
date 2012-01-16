#ifndef DRAWER_H
#define DRAWER_H

#include "QtGui"
#include <Parser.h>

class FuntionDrawer{
public:
    FuntionDrawer(vector<point>* result, QGraphicsScene* scene);
    void drawGridLines();
    void drawGraph();
private:
    QGraphicsScene* scene;
    vector<point>* result;

    double minY;
    double maxY;

    double minX;
    double maxX;
    double logBase;

    void scaleToScene ();
    void addXaxe(double y);
    void addYaxe(double x);

    double findMax ();
    double findMin();
    QString stringify(double x);
};

#endif // DRAWER_H
