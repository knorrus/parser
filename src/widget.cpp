#include "widget.h"
#include "ui_widget.h"
#include "string";
#include <Parser.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene();

    scene->setSceneRect(0,0,700,400);
    ui->canvas->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}

QVector<QPoint> loadPoints (vector<point> result){
    QVector<QPoint> points;
    vector<point>::iterator iter;
    point p;
    for(iter = result.begin(); iter != result.end(); iter++ ) {
        p = *iter;
        points.append(QPoint(p.first, p.second));
    }
    return points;
};

void Widget::on_check_clicked()
{
    QByteArray arr = ui->functionName->text().toAscii();
    char *function = arr.data();

    ui->intervalStart->setInputMask("0.00");
    ui->intervalStart->setMaxLength(10);

    ui->intervalEnd->setInputMask("0.00");
    ui->intervalEnd->setMaxLength(10);


    double start = ui->intervalStart->text().toDouble();
    double end = ui->intervalEnd->text().toDouble();
    ui->canvas->scene();
    Parser* parser = new Parser();

    vector<point> resultVector = parser->tabulate(start, end, function);
    QVector<QPoint> Qpoints(loadPoints(resultVector));
    delete parser;
}





