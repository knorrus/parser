#include "graphicscanvas.h"

GraphicsCanvas::GraphicsCanvas(QWidget *parent) :
    QGraphicsView(parent)
{

}


void GraphicsCanvas::resizeEvent(QResizeEvent *event){
    on_resize(event);
}
