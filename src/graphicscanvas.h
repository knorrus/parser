#ifndef GRAPHICSCANVAS_H
#define GRAPHICSCANVAS_H

#include <QGraphicsView>

class GraphicsCanvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsCanvas(QWidget *parent = 0);

signals:
    void on_resize(QResizeEvent *event);
public slots:
    void resizeEvent(QResizeEvent *event);
};

#endif // GRAPHICSCANVAS_H
