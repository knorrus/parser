#include "Drawer.h"
#include <sstream>
#include "math.h"
using namespace std;

double dAbs (double value) {
    return value < 0 ? -value : value;
}

FuntionDrawer::FuntionDrawer(vector<point>* result, QGraphicsScene* scene, double start, double end){
    this->result = result;
    this->scene = scene;
    this->maxY = this->findMax();
    this->minY = this->findMin();
    this->minX = start;
    this->maxX = end;

    this->labelFont = QFont("Helvetica [Cronyx]", 8);
    this->labelFont.setStretch(QFont::SemiCondensed);

   this->xLabelCount = scene->width()/25;
   this->yLabelCount = scene->height()/25;

    this->xLogBase = log10(maxX-minX);
    xLogBase < 0 ? xLogBase = floor(xLogBase) :  xLogBase = ceil(xLogBase);
    xLogPow = dAbs(xLogBase);
    xLogPow = round(exp(xLogPow * log(10)));
    this->yLogBase = log10(maxY-minY);
    yLogBase < 0 ? yLogBase = floor(yLogBase) :  yLogBase = ceil(yLogBase);
    yLogPow = dAbs(yLogBase);
    yLogPow = round(exp(yLogPow * log(10)));
    this->scaleToScene();
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

QString FuntionDrawer::stringifyX(double x) {
    stringstream ss;
    if (xLogBase > 2){
        x > 0 ? x = round(x) : x = floor(x);
    }
    x > 0 ? x = ceil(x*xLogPow)/xLogPow : x = floor(x*xLogPow)/xLogPow;
    ss << x;
    return QString::fromStdString(ss.str());
}

QString FuntionDrawer::stringifyY(double y) {
    stringstream ss;
    if (yLogBase > 2){
        y > 0 ? y = round(y) : y = floor(y);
    }
    y > 0 ? y = ceil(y*yLogPow)/yLogPow : y = floor(y*yLogPow)/yLogPow;
    ss << y;
    return QString::fromStdString(ss.str());
}


void FuntionDrawer::addXaxe(double y) {
    QPen pen(QColor(0, 0, 128), 2);
    scene->addLine(0, y, scene->width(), y, pen);
    QGraphicsTextItem *text = scene->addText(stringifyY(0), labelFont);
    text->setX(0);
    text->setY(y);
    text->setDefaultTextColor(QColor(0, 0, 238));
}

void FuntionDrawer::addYaxe(double x) {
    QPen pen(QColor(0, 0, 128), 2);
    scene->addLine(x, 0, x, scene->height(), pen);
    QGraphicsTextItem *text = scene->addText(stringifyX(0), labelFont);
    text->setX(x);
    text->setY(scene->height()-20);
    text->setDefaultTextColor(QColor(0, 0, 238));
}


void FuntionDrawer::addHorizontalLines(double begin, double end, double step, double label){
    QPen pen(QColor(205, 92, 92), 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    double yStep = (maxY-minY)/yLabelCount;
    double yCurrent = label;
    for (int i = begin; i<= end; i+=step){
        this->scene->addLine(20, i, this->scene->width(), i,  pen);
        if (yCurrent - yStep >= minY){
            QGraphicsTextItem *text = scene->addText(stringifyY(yCurrent), labelFont);
            text->setX(0);
            text->setY(i);
            text->setDefaultTextColor(QColor(0, 0, 238));
            yCurrent -= yStep;
        }
    }
}

void FuntionDrawer::addVerticalLines(double begin, double end, double step, double label){
    QPen pen(QColor(205, 92, 92), 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    double xStep = (maxX-minX)/xLabelCount;
    double xCurrent = label;
    for (int i = begin; i<= end; i+=step){
        this->scene->addLine(i, 0, i, this->scene->height()-20, pen);
        if (xCurrent + xStep <= maxX){
            QGraphicsTextItem *text = scene->addText(stringifyX(xCurrent), labelFont);
            text->setX(i);
            text->setY(scene->height()-20);
            text->setDefaultTextColor(QColor(0, 0, 238));
            xCurrent += xStep;
        };
    };
}

void FuntionDrawer::drawGridLines(){   


        addVerticalLines(0, scene->width(), 25, minX);
        addHorizontalLines(0,scene->height()-20, 25, maxY);


/*    if ((minY*maxY <= 0) && (minX*maxX > 0)){
        double yScale = scene->height()/(maxY-minY);
        double zero = scene->height()+minY*yScale;
        addHorizontalLines(zero+25, scene->height(), 25, -(maxY-minY)/20.0);
        addXaxe(zero);
        addHorizontalLines(0, zero, 25, maxY);
        addVerticalLines(0, scene->width(), 25, minX);
    }

    if ((minY*maxY > 0) && (minX*maxX <= 0)){
        double xScale = scene->width()/(maxX-minX);
        double zero = -minX*xScale;        
        addHorizontalLines(0, scene->height(), 25, maxY);
        addVerticalLines(zero+25, scene->width(), 25, (maxX-minX)/20.0);
        addYaxe(zero);
        addVerticalLines(0, zero-25, 25, minX);
    }

    if ((minY*maxY <= 0) && (minX*maxX <= 0)){
        double yScale = scene->height()/(maxY-minY);
        double zero = scene->height()+minY*yScale;
        addHorizontalLines(0, zero-25, 25, maxY);
        addXaxe(zero);
        addHorizontalLines(zero+25, scene->height(),25, -(maxY-minY)/20.0);

        double xScale = scene->width()/(maxX-minX);
        zero = -minX*xScale;                  
        addVerticalLines(zero+25, scene->width(), 25, (maxX-minX)/20.0);
        addYaxe(zero);
        addVerticalLines(0, zero-25, 25, minX);
    }; */
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
