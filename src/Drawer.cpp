#include "Drawer.h"


void Drawer::drawGridLines(QGraphicsScene* scene){
    QPen pen(QColor(205, 92, 92), 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
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

QVector<QPoint> Drawer::scaleToScene (vector<point> result, QGraphicsScene* scene){
    QVector<QPoint> points;
    vector<point>::iterator iter;
    point p;

    double minY = this->findMin(result);
    double maxY = this->findMax(result);
    double minX = result.front().first;
    double maxX = result.back().first;

    double yScale = scene->height()/(maxY-minY);
    double xScale = scene->width()/(maxX-minX);

    double yShift = minY*yScale < 0 ? scene->height()+minY*yScale : scene->height()-minY*yScale;
    double xShift = minX*xScale < 0 ? scene->width()+minX*xScale : scene->width()-minX*xScale;

    vector<point>::iterator itr = result.begin();

    while( itr != result.end() ){
        p = *itr;
        points.append(QPoint(((p.first-minX)*xScale), (scene->height()-(p.second-minY)*yScale)));
        itr++;
    }
    return points;
};

double Drawer::findMax(vector<point> result){
    double max = result.at(0).second;
    point temp;
    vector<point>::iterator iter;
    for (iter=result.begin(); iter != result.end(); iter++){
        temp = *iter;
        if (temp.second > max)
            max = temp.second;
    }
    return max;
}

double Drawer::findMin(vector<point> result){
    double min = result.at(0).second;
    point temp;
    vector<point>::iterator iter;
    for (iter=result.begin(); iter != result.end(); iter++){
        temp = *iter;
        if (temp.second < min)
            min = temp.second;
    }
    return min;
}
