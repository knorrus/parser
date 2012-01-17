#include <QtGui/QApplication>
#include "widget.h"
#include "QIcon"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QIcon icon("../resources/graph-icon128x128.png");
    a.setWindowIcon(icon);
    w.show();
    return a.exec();
}
