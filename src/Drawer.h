#ifndef DRAWER_H
#define DRAWER_H

#include "QtGui"
#include <Parser.h>

class FuntionDrawer{
public:
    FuntionDrawer(vector<point>* result, QGraphicsScene* scene);
    void drawGridLines();
    void drawGraph();
protected:
    void scaleToScene ();
    QString stringify(double x);\
    void addXaxe(double y);
    void addYaxe(double x);
private:
    QGraphicsScene* scene;
    vector<point>* result;
    double minY;
    double maxY;
    double minX;
    double maxX;
    double logBase;
    double logPow;
    double findMax ();
    double findMin();

};

#endif // DRAWER_H
