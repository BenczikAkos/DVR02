#include "transferfunceditorcanvas.h"

TransferFuncEditorCanvas::TransferFuncEditorCanvas(QWidget* parent) :
    QWidget(parent),
    funcProperty(std::make_unique<TransferFuncProperty>()){}

void TransferFuncEditorCanvas::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int width = this->width(); int height = this->height();
    painter.translate(width/50.0, height*0.98);
    painter.scale(width / 300.0, -height / 300.0);
    auto opacities = funcProperty->getAllOpacities();
    auto intensities = funcProperty->getAllIntensities();
    auto colors = funcProperty->getAllColors();
    painter.setPen(Qt::NoPen);
    auto radiusX = pointSize / width; auto radiusY = pointSize / height;
    auto prevPoint = QPointF();
    QPen linePen(Qt::black);
    linePen.setWidth(300.0 / qMin(width, height));
    for (int i = 0; i < opacities.size(); ++i) {
        auto currPoint = QPointF(intensities.at(i), opacities.at(i));
        painter.setBrush(colors.at(i));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(currPoint, radiusX, radiusY);
        if (i > 0) {
            painter.setPen(linePen);
            painter.drawLine(prevPoint, currPoint);
        }
        prevPoint = currPoint;
    }
}