#include "Drawer.h"

void Drawer::drawGridLines(QGraphicsScene* scene){
   QPen pen(Qt::gray, 0.1);
   for (int i = 0; i<= scene->width(); i+=25){
        scene->addLine(i, 0, i, scene->height(), pen);
   };
   for (int i = 0; i<= scene->height(); i+=25){
        scene->addLine(0, i, scene->width(), i,  pen);
    }
}

void Drawer::drawGraph(QVector<QPoint> points, QGraphicsScene* scene){
    QVector<QPoint>::iterator iter;
    QPoint _point;
    QPoint _next;

    for(iter = points.begin(); iter!=points.end(); iter++){
        _point = *iter;
        _next = *++iter;
        if (_next == points.last()){break;}
        iter--;
        scene->addLine(_point.x(), _point.y(), _next.x(), _next.y());
    }
}

