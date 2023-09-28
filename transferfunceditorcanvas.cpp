#include "transferfunceditorcanvas.h"

void TransferFuncEditorCanvas::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QWidget::paintEvent(event);
    QLineF line(10.0, 80.0, 90.0, 20.0);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::blue);
    painter.drawLine(line);
}