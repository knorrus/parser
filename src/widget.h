#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Drawer.h>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_check_clicked();
    void on_canvas_resize(QResizeEvent *event);
    void on_print_clicked();

private:
    Ui::Widget *ui;
    FuntionDrawer* drawer;
    vector<point> resultVector;
};

#endif // WIDGET_H
