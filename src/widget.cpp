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
    ui->print->setEnabled(true);

    /*  ui->intervalStart->setInputMask("0.00");
    ui->intervalStart->setMaxLength(10);
    ui->intervalEnd->setInputMask("0.00");
    ui->intervalEnd->setMaxLength(10);
*/
    double start = ui->intervalStart->text().toDouble();
    double end = ui->intervalEnd->text().toDouble();

    QGraphicsScene *scene = ui->canvas->scene();
    scene->clear();

    Parser* parser = new Parser();
    vector<point> resultVector = parser->tabulate(start, end, function);

    FuntionDrawer* drawer = new FuntionDrawer(&resultVector, scene);
    drawer->drawGridLines();
    drawer->drawGraph();

    scene->update();

    delete parser;
    delete drawer;
}

void Widget::on_print_clicked()
{
    QGraphicsScene *scene = ui->canvas->scene();
    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    if( QPrintDialog(&printer).exec() == QDialog::Accepted ){
        QPainter painter(&printer);
        scene->render(&painter);
        painter.begin(&printer);
        painter.end();
    }
}
