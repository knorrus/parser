#ifndef DRAWER_H
#define DRAWER_H

#include "QtGui"
#include <Parser.h>

class FuntionDrawer{
public:
    FuntionDrawer(vector<point>* result, QGraphicsScene* scene, double start, double end);
    void drawGridLines();
    void drawGraph();    
    /*Scale to scene: converting graph points to scena rectangle */
    void scaleToScene ();
    inline void setVector (vector<point>* result)
        { this->result = result; }
protected:

    /*Converting double to string with given accuracy */
    QString stringifyX(double x);
    QString stringifyY(double y);

    QFont labelFont;

    void addXaxe(double y);
    void addYaxe(double x);
    void addHorizontalLines (double begin, double end, double step, double label);
    void addVerticalLines (double begin, double end, double step, double label);    
private:
    QGraphicsScene* scene;
    vector<point>* result;
    double minY;
    double maxY;
    double minX;
    double maxX;
    double xLogBase; //log10 of the Y graph diapasone
    double xLogPow;  //10^logBase
    double yLogBase; //log10 of the Y graph diapasone
    double yLogPow;  //10^logBase

    double xLabelCount;
    double yLabelCount;

    double findMax ();
    double findMin();

};

#endif // DRAWER_H
