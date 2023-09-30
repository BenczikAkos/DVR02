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
    //painter.translate(width / 2, height / 2);
    //painter.translate(0.0, height);
    painter.scale(width / 255.0, height / 255.0);
    auto opacities = funcProperty->getAllOpacities();
    auto intensities = funcProperty->getAllIntensities();
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    painter.setBrush(Qt::ConicalGradientPattern);
    auto minSize = qMin(width, height);
    auto radius = qMin(minSize / 300.0, 2.0);
    for (int i = 0; i < opacities.size(); ++i) {
        painter.drawEllipse(QPointF(intensities.at(i), opacities.at(i)), radius/300.0, radius/300.0);
    }
}