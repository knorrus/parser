#include "Drawer.h"
#include <sstream>
#include "math.h"
using namespace std;

double dAbs (double value) {
    return value < 0 ? -value : value;
}

FuntionDrawer::FuntionDrawer(vector<point>* result, QGraphicsScene* scene, double start, double end){
    this->result = result;
    this->scaledPoints = new vector<point>();
    this->scene = scene;

    this->maxY = this->findMax();
    this->minY = this->findMin();

    this->minX = start;
    this->maxX = end;

    this->labelFont = QFont("Helvetica [Cronyx]", 8);
    this->labelFont.setStretch(QFont::SemiCondensed);

    this->lineCount = 20;

    this->xLogBase = log10(maxX-minX);
    xLogBase < 0 ? xLogBase = floor(xLogBase)-1 :  xLogBase = ceil(xLogBase);
    xLogPow = dAbs(xLogBase);
    xLogPow = round(exp(xLogPow * log(10)));

    this->yLogBase = log10(maxY-minY);
    yLogBase < 0 ? yLogBase = floor(yLogBase)-1 :  yLogBase = ceil(yLogBase);
    yLogPow = dAbs(yLogBase);
    yLogPow = round(exp(yLogPow * log(10)));

    this->scaleToScene();
}

void FuntionDrawer::drawGraph(){
    vector<point>::iterator iterator = this->scaledPoints->begin();
    point first = *iterator++, second = *iterator++;
    while(iterator !=  this->scaledPoints->end()){
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


void FuntionDrawer::addXaxe(double y, double step) {
    QPen axePen(QColor(0, 0, 128), 2);
    QPen pen(QColor(205, 92, 92), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    double yStep = (maxY-minY)/lineCount;
    double yCurrent;
    yCurrent = yStep;
    for (int i = y-step; i >= 0; i-=step){
        this->scene->addLine(20, i, scene->width(), i,  pen);
        if (yCurrent - yStep >= minY){
            QGraphicsTextItem *text = scene->addText(stringifyY(yCurrent), labelFont);
            text->setX(0);
            text->setY(i);
            text->setDefaultTextColor(QColor(0, 0, 238));
            yCurrent += yStep;
        }
    }
    scene->addLine(20, y, scene->width(), y, axePen);
    QGraphicsTextItem *text = scene->addText(stringifyY(0), labelFont);
    text->setX(0);
    text->setY(y-10);
    text->setDefaultTextColor(QColor(0, 0, 238));
    yCurrent = -yStep;
    for (int i = y+step; i <= scene->height()-20; i+=step){
        this->scene->addLine(20, i, scene->width(), i,  pen);
        if (yCurrent + yStep <= maxY){
            QGraphicsTextItem *text = scene->addText(stringifyY(yCurrent), labelFont);
            text->setX(0);
            text->setY(i-20);
            text->setDefaultTextColor(QColor(0, 0, 238));
            yCurrent -= yStep;
        }
    }
}

void FuntionDrawer::addYaxe(double x, double step) {
    QPen axePen(QColor(0, 0, 128), 2);
    x+=10;
    QPen pen(QColor(205, 92, 92), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    double xStep = (maxX-minX)/lineCount;
    double xCurrent;
    //add lines x<0
    xCurrent = -xStep;
    for (int i = x-step; i >= 20; i-=step){
        this->scene->addLine(i, 0, i, this->scene->height()-20, pen);
        if (xCurrent >= minX){
            QGraphicsTextItem *text = scene->addText(stringifyX(xCurrent), labelFont);
            text->setX(i);
            text->setY(scene->height()-20);
            text->setDefaultTextColor(QColor(0, 0, 238));
            xCurrent -= xStep;
        }
    };
    //add axe
    scene->addLine(x, 0, x, scene->height()-25, axePen);
    QGraphicsTextItem *text = scene->addText(stringifyX(0), labelFont);
    text->setX(x);
    text->setY(scene->height()-20);
    text->setDefaultTextColor(QColor(0, 0, 238));
    //add lines x>0
    xCurrent = xStep;
    for (int i = x+step; i <= scene->width(); i+=step){
        this->scene->addLine(i, 0, i, this->scene->height()-20, pen);
        if (xCurrent <= maxX){
            QGraphicsTextItem *text = scene->addText(stringifyX(xCurrent), labelFont);
            text->setX(i);
            text->setY(scene->height()-20);
            text->setDefaultTextColor(QColor(0, 0, 238));
            xCurrent += xStep;
        }
    };
}

void FuntionDrawer::addHorizontalLines(double begin, double end, double step, double label){
    QPen pen(QColor(205, 92, 92), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    double yStep = (maxY-minY)/lineCount;
    double yCurrent = label;
    for (int i = begin; i<= end; i+=step){
        this->scene->addLine(20, i, scene->width(), i,  pen);
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
    QPen pen(QColor(205, 92, 92), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    double xStep = (maxX-minX)/lineCount;
    double xCurrent = label;
    for (int i = begin; i<= end; i+=step){
        this->scene->addLine(i, 0, i, this->scene->height()-20, pen);
        if (xCurrent + xStep <= maxX){
            QGraphicsTextItem *text = scene->addText(stringifyX(xCurrent), labelFont);
            text->setX(i+20);
            text->setY(scene->height()-25);
            text->setDefaultTextColor(QColor(0, 0, 238));
            xCurrent += xStep;
        };
    };
}

void FuntionDrawer::drawGridLines(){   

    if ((minY*maxY > 0) && (minX*maxX > 0)){
        addVerticalLines(0, scene->width()-20, (int)scene->width()/lineCount, minX);
        addHorizontalLines(0,scene->height()-20, (int)scene->height()/lineCount, maxY);
    }

    if ((minY*maxY <= 0) && (minX*maxX > 0)){
        double yScale = scene->height()/(maxY-minY);
        double zero = scene->height()+minY*yScale;       
        addXaxe(zero, (int)scene->height()/lineCount);
        addVerticalLines(0, scene->width()-20, (int)scene->width()/lineCount, minX);
    }

    if ((minY*maxY > 0) && (minX*maxX <= 0)){
        double xScale = scene->width()/(maxX-minX);
        double zero = -minX*xScale;        
        addHorizontalLines(0, scene->height()-20, (int)scene->height()/lineCount, maxY);
        addYaxe(zero, (int)scene->width()/lineCount);
    }

    if ((minY*maxY <= 0) && (minX*maxX <= 0)){
        double yScale = scene->height()/(maxY-minY);
        double zero = scene->height()+minY*yScale;
        addXaxe(zero,(int)scene->height()/lineCount);
        double xScale = scene->width()/(maxX-minX);
        zero = -minX*xScale;                  
        addYaxe(zero, (int)scene->width()/lineCount);
    };
}

void FuntionDrawer::scaleToScene (){
    scaledPoints->clear();
    double yScale = (scene->height()-20)/(maxY-minY);
    double xScale = (scene->width()-20)/(maxX-minX);
    vector<point>::iterator itr = this->result->begin();
    point temp;
    while( itr != this->result->end() ){
        temp.first = ((*itr).first-minX)*xScale+20;
        temp.second = scene->height()-((*itr).second-this->minY)*yScale-20;
        temp.type = (*itr).type;
        scaledPoints->push_back(temp);
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
