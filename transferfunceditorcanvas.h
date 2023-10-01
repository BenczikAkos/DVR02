#pragma once
#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include "transferfuncproperty.h"

class TransferFuncEditorCanvas : public QWidget {
	Q_OBJECT
public:
	explicit TransferFuncEditorCanvas(QWidget* parent = nullptr, std::shared_ptr<TransferFuncProperty> _funcProperty = nullptr);
signals:
	void intensityOpacityChangedAt(int index, float newIntensity, float newOpacity);
	void colorChangedAt(int index, QColor newColor);
protected:
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
private:
	QTransform t_device2func;
	QTransform t_func2device;
	float pointSize = 1000.0f;
	std::shared_ptr<TransferFuncProperty> funcProperty;
	bool moving = false;
	int activePointIndex = -1;
};
