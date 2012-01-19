#include "widget.h"
#include "ui_widget.h"
#include "string"
#include <Parser.h>
#include <Drawer.h>
#include <QGraphicsScene>
#include "graphicscanvas.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    GraphicsCanvas* canvas = new GraphicsCanvas();
    ui->setupUi(this);
    delete ui->canvas;
    ui->canvas = canvas;
    ui->verticalLayout_2->addWidget(ui->canvas);
    QGraphicsScene *scene = new QGraphicsScene();      
    ui->canvas->setScene(scene);
    drawer = NULL;
    connect(canvas, SIGNAL(on_resize(QResizeEvent*)), SLOT(on_canvas_resize(QResizeEvent*)));
}

Widget::~Widget()
{
    delete ui;
    delete drawer;
}

void Widget::on_canvas_resize(QResizeEvent *event){
    ui->canvas->scene()->setSceneRect(5, 5, ui->canvas->width()-10, ui->canvas->height()-10);
    if (drawer != NULL){
        ui->canvas->scene()->clear();
        drawer->scaleToScene();
        drawer->drawGridLines();
        drawer->drawGraph();
    }
}

void Widget::on_check_clicked()
{
    QByteArray arr = ui->functionName->text().toAscii();
    QMessageBox msgBox;
    char *function = arr.data();
    ui->print->setEnabled(true);
    ui->intervalStart->setValidator(new QDoubleValidator());
    ui->intervalStart->setMaxLength(6);
    ui->intervalEnd->setValidator(new QDoubleValidator());
    ui->intervalEnd->setMaxLength(6);
    double start = ui->intervalStart->text().toDouble();
    double end = ui->intervalEnd->text().toDouble();
    if (start >= end){
        msgBox.setText("Wrong diapasone");
        msgBox.exec();
        return;
    }
    QGraphicsScene *scene = ui->canvas->scene();
    if (ui->clearPrevious->isChecked()){
        scene->clear();
    }
    Parser* parser = new Parser();
    try {
        resultVector = parser->tabulate(start, end, scene->width(), function);
    }
    catch (ErrorCodes err) {
        msgBox.setText("Wrong function: " + ui->functionName->text());
        msgBox.exec();
        return;
    }
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
