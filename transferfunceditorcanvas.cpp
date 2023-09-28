#include "transferfunceditorcanvas.h"

TransferFuncEditorCanvas::TransferFuncEditorCanvas(QWidget* parent) :
    QWidget(parent)
{
}

void TransferFuncEditorCanvas::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int side = qMin(width(), height());
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    QLineF line(10.0, 80.0, 90.0, 20.0);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::blue);
    painter.drawLine(line);
}