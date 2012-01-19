#include "widget.h"
#include "ui_widget.h"
#include "string"
#include <Parser.h>
#include <Drawer.h>
#include <QGraphicsScene>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene();   
    ui->canvas->setScene(scene);
    windowSize = QSize(this->width(), this->height());
    drawer = NULL;
}

Widget::~Widget()
{
    delete ui;
    delete drawer;
}

void Widget::resizeEvent(QResizeEvent *event){
    ui->canvas->scene()->setSceneRect(5, 5, ui->canvas->width()-10, ui->canvas->height()-10);

        if (drawer != NULL){
            ui->canvas->scene()->clear();
           // drawer->scaleToScene();
            drawer->drawGridLines();
          //  drawer->drawGraph();



    }
}

void Widget::on_check_clicked()
{
    QByteArray arr = ui->functionName->text().toAscii();
    char *function = arr.data();
    ui->print->setEnabled(true);
    ui->intervalStart->setValidator(new QDoubleValidator());
    ui->intervalStart->setMaxLength(6);
    ui->intervalEnd->setValidator(new QDoubleValidator());
    ui->intervalEnd->setMaxLength(6);
    double start = ui->intervalStart->text().toDouble();
    double end = ui->intervalEnd->text().toDouble();
    QGraphicsScene *scene = ui->canvas->scene();
    if (ui->clearPrevious->isChecked()){
        scene->clear();
    }
    Parser* parser = new Parser();
    resultVector = parser->tabulate(start, end, scene->width()/2, function);
    drawer = new FuntionDrawer(&resultVector, scene, start, end);
    drawer->drawGridLines();
    drawer->drawGraph();
    scene->update();
    ui->authors->setText("authors: Knorr, Boyko");
    delete parser;

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
