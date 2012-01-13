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

void Drawer::drawGraph(vector<point> points, QGraphicsScene* scene){
    vector<point>::iterator iterator = points.begin();

    point first = *iterator++, second = *iterator++;

    while(iterator != points.end()){

        if ((first.type == GRAPHPOINT) && (second.type == GRAPHPOINT)){
            scene->addLine(first.first, first.second, second.first, second.second);
        }

        first = second;
        second = *iterator++;

    }
}

vector<point> Drawer::scaleToScene (vector<point> result, QGraphicsScene* scene){
    point thePoint;

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

        (*itr).first = ((*itr).first-minX)*xScale;
        (*itr).second = scene->height()-((*itr).second-minY)*yScale;
        itr++;
    }
    return result;
};

double Drawer::findMax(vector<point> result){
    vector<point>::iterator iter = result.begin();
    double max;
    point temp = result.front();
    while ((temp.type != GRAPHPOINT) && (iter != result.end())){
        temp = *iter++;
    }
    max = temp.second;
    for (iter; iter != result.end(); iter++){
        temp = *iter;
        if ((temp.second > max) && (temp.type == GRAPHPOINT))
            max = temp.second;
    }
    return max;
}

double Drawer::findMin(vector<point> result){
    vector<point>::iterator iter = result.begin();
    double min;
    point temp = result.front();
    while ((temp.type != GRAPHPOINT) && (iter != result.end())){
        temp = *iter++;
    }
    min = temp.second;
    for (iter; iter != result.end(); iter++){
        temp = *iter;
        if ((temp.second < min) && (temp.type == GRAPHPOINT)){
            min = temp.second;
        }
    }
    return min;
}
