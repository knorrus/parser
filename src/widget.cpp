#include "widget.h"
#include "ui_widget.h"
#include "string";
#include <Parser.h>
#include <Drawer.h>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,500,500);
    ui->canvas->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_check_clicked()
{

    QByteArray arr = ui->functionName->text().toAscii();
    char *function = arr.data();

    /*  ui->intervalStart->setInputMask("0.00");
    ui->intervalStart->setMaxLength(10);

    ui->intervalEnd->setInputMask("0.00");
    ui->intervalEnd->setMaxLength(10);
*/

    double start = ui->intervalStart->text().toDouble();
    double end = ui->intervalEnd->text().toDouble();

    QGraphicsScene *scene = ui->canvas->scene();
    Parser* parser = new Parser();
    vector<point> resultVector = parser->tabulate(start, end, function);
    Drawer* drawer = new Drawer();
    scene->clear();
    drawer->drawGridLines(scene);
    QVector<QPoint> points =  drawer->scaleToScene(resultVector, scene);
    drawer->drawGraph(points, scene);
    scene->update();

    delete parser;
}
