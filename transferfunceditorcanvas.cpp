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
    painter.setTransform(t_func2device, true);
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

void TransferFuncEditorCanvas::resizeEvent(QResizeEvent* event)
{
    auto newSize = event->size();
    auto width = newSize.width(); auto height = newSize.height();
    t_func2device = QTransform().translate(width / 50.0, height * 0.98).scale(width / 300.0, -height / 300.0);
    t_device2func = t_func2device.inverted();
}

void TransferFuncEditorCanvas::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    auto funcPos = event->pos() * t_device2func;
    auto opacities = funcProperty->getAllOpacities();
    auto intensities = funcProperty->getAllIntensities();
    qreal distance = -1;
    for (int i = 0; i < opacities.size(); ++i) {
        auto currPoint = QPointF(intensities.at(i), opacities.at(i));
        qreal d = QLineF(funcPos, currPoint).length();
        if ((distance < 0 && d < 8 * pointSize/width()) || d < distance) {
            distance = d;
            activePointIndex = i;
        }
    }
}

void TransferFuncEditorCanvas::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    if (activePointIndex >= 0)
    {
        auto funcPos = event->pos() * t_device2func;
        funcProperty->intensityOpacityChangedAt(activePointIndex, funcPos.x(), funcPos.y());
    }
    update();
}

void TransferFuncEditorCanvas::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    activePointIndex = -1;
}
