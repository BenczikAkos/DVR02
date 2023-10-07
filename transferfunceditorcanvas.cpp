#include "transferfunceditorcanvas.h"

TransferFuncEditorCanvas::TransferFuncEditorCanvas(QWidget* parent, std::shared_ptr<TransferFuncProperty> _funcProperty) :
    QWidget(parent),
    funcProperty(_funcProperty)
{
    QObject::connect(this, SIGNAL(intensityOpacityChangedAt(int, float, float)), funcProperty.get(), SLOT(intensityOpacityChangedAt(int, float, float)));
}

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
    linePen.setWidth(3);
    linePen.setWidth(300.0 / qMin(width, height));
    for (int i = 0; i < opacities.size(); ++i) 
    {
        auto currPoint = QPointF(intensities.at(i), opacities.at(i));
        if (i > 0) 
        {
            painter.setPen(linePen);
            painter.drawLine(prevPoint, currPoint);
        }
        painter.setBrush(colors.at(i));
        if (i == activePointIndex) 
        {
            painter.setPen(Qt::black);
        }
        else
        {
            painter.setPen(Qt::NoPen);
        }
        painter.drawEllipse(currPoint, radiusX, radiusY);
        prevPoint = currPoint;
        update();
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
    activePointIndex = -1;
    qreal distance = -1;
    for (int i = 0; i < opacities.size(); ++i) 
    {
        auto currPoint = QPointF(intensities.at(i), opacities.at(i));
        qreal d = QLineF(funcPos, currPoint).length();
        if ((distance < 0 && d < 8 * pointSize/width()) || d < distance) 
        {
            distance = d;
            activePointIndex = i;
        }
    }
    if (activePointIndex >= 0) 
    {
        mouseMoving = true;
        emit selectedPointColor(funcProperty->getAllColors().at(activePointIndex));
    }
}

void TransferFuncEditorCanvas::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);
    if (activePointIndex >= 0 && mouseMoving)
    {
        auto funcPos = event->pos() * t_device2func;
        emit intensityOpacityChangedAt(activePointIndex, funcPos.x(), funcPos.y());
    }
    update();
}

void TransferFuncEditorCanvas::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);
    mouseMoving = false;
}

void TransferFuncEditorCanvas::mouseDoubleClickEvent(QMouseEvent* event)
{
    QWidget::mouseDoubleClickEvent(event);
    auto buton = event->button();
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        auto funcPos = event->pos() * t_device2func;
        funcProperty->addKey(funcPos.x(), QColor(100, 100, 100, funcPos.y()));
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
        funcProperty->removeKeyAt(activePointIndex);
    }
}
