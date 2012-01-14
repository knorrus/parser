#include "Drawer.h"


FuntionDrawer::FuntionDrawer(vector<point>* result, QGraphicsScene* scene){
    this->result = result;
    this->scene = scene;

    this->maxY = this->findMax();
    this->minY = this->findMin();

    this->minX = this->result->front().first;
    this->maxX = this->result->back().first;

    this->scaleToScene();
}


double dAbs (double value) {
    return value < 0 ? -value : value;
}

void FuntionDrawer::drawGridLines(){
    QPen pen(QColor(205, 92, 92), 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    if ((minY*maxY > 0) && (minX*maxX > 0)){
        //verical
        for (int i = 0; i<= this->scene->width(); i+=25){
            this->scene->addLine(i, 0, i, this->scene->height(), pen);
        };
        //horizontal
        for (int i = 0; i<= this->scene->height(); i+=25){
            this->scene->addLine(0, i, this->scene->width(), i,  pen);
        }
    }
    if ((minY*maxY<=0) && (minX*maxX > 0)){
        double yScale = scene->height()/(maxY-minY);
        double zero = scene->height()+minY*yScale;
        addXaxe(zero);
        //horizontal under zero
        for (int i = zero+25; i<= this->scene->height(); i+=25){
            this->scene->addLine(0, i, this->scene->width(), i,  pen);
        }
        //horizontal before zero
        for (int i = zero-25; i>=0; i-=25){
            this->scene->addLine(0, i, this->scene->width(), i,  pen);
        }
        //verical
        for (int i = 0; i<= this->scene->width(); i+=25){
            this->scene->addLine(i, 0, i, this->scene->height(), pen);
        };
    }
    if ((minY*maxY > 0) && (minX*maxX <= 0)){
        double xScale = scene->width()/(maxX-minX);
        double zero = -minX*xScale;
        addYaxe(zero);
        //vertical under zero
        for (int i = zero+25; i<= this->scene->width(); i+=25){
            this->scene->addLine(i, 0, i, scene->height(),  pen);
        }
        //vertical before zero
        for (int i = zero-25; i>=0; i-=25){
            this->scene->addLine(i, 0, i, scene->height(),  pen);
        }

        //horizontal
        for (int i = 0; i<= this->scene->height(); i+=25){
            this->scene->addLine(0, i, this->scene->width(), i,  pen);
        }
    }
    if ((minY*maxY <= 0) && (minX*maxX <= 0)){
        double yScale = scene->height()/(maxY-minY);
        double zero = scene->height()+minY*yScale;
        addXaxe(zero);
        //horizontal under zero
        for (int i = zero+25; i<= this->scene->height(); i+=25){
            this->scene->addLine(0, i, this->scene->width(), i,  pen);
        }
        //horizontal before zero
        for (int i = zero-25; i>=0; i-=25){
            this->scene->addLine(0, i, this->scene->width(), i,  pen);
        }
        double xScale = scene->width()/(maxX-minX);
        zero = -minX*xScale;
        addYaxe(zero);
        //vertical under zero
        for (int i = zero+25; i<= this->scene->width(); i+=25){
            this->scene->addLine(i, 0, i, scene->height(),  pen);
        }
        //vertical before zero
        for (int i = zero-25; i>=0; i-=25){
            this->scene->addLine(i, 0, i, scene->height(),  pen);
        }
    };
}

void FuntionDrawer::drawGraph(){
    vector<point>::iterator iterator = this->result->begin();
    point first = *iterator++, second = *iterator++;
    while(iterator !=  this->result->end()){
        if ((first.type == GRAPHPOINT) && (second.type == GRAPHPOINT)){
            this->scene->addLine(first.first, first.second, second.first, second.second);
        }
        first = second;
        second = *iterator++;
    }
}

void FuntionDrawer::scaleToScene (){   

    double yScale = scene->height()/(maxY-minY);
    double xScale = scene->width()/(maxX-minX);

    vector<point>::iterator itr = this->result->begin();
    while( itr != this->result->end() ){
        (*itr).first = ((*itr).first-minX)*xScale;
        (*itr).second = scene->height()-((*itr).second-this->minY)*yScale;
        itr++;
    }
};

void FuntionDrawer::addXaxe(double y) {
    QPen pen(QColor(0, 0, 128), 2);
    scene->addLine(0, y, scene->width(), y, pen);
}

void FuntionDrawer::addYaxe(double x) {
    QPen pen(QColor(0, 0, 128), 2);
    scene->addLine(x, 0, x, scene->height(), pen);
}

double FuntionDrawer::findMax(){
    vector<point>::iterator iter = this->result->begin();
    double max;
    point temp = this->result->front();
    while ((temp.type != GRAPHPOINT) && (iter != this->result->end())){
        temp = *iter++;
    }
    max = temp.second;
    for (iter; iter != this->result->end(); iter++){
        temp = *iter;
        if ((temp.second > max) && (temp.type == GRAPHPOINT))
            max = temp.second;
    }
    return max;
}

double FuntionDrawer::findMin(){
    vector<point>::iterator iter = this->result->begin();
    double min;
    point temp = this->result->front();
    while ((temp.type != GRAPHPOINT) && (iter != this->result->end())){
        temp = *iter++;
    }
    min = temp.second;
    for (iter; iter != this->result->end(); iter++){
        temp = *iter;
        if ((temp.second < min) && (temp.type == GRAPHPOINT)){
            min = temp.second;
        }
    }
    return min;
}
