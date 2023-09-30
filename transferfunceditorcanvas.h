#pragma once
#include <QWidget>
#include <QPainter>
#include <QResizeEvent>
#include "transferfuncproperty.h"

class TransferFuncEditorCanvas : public QWidget {
	Q_OBJECT
public:
	explicit TransferFuncEditorCanvas(QWidget* parent = nullptr);
protected:
	void paintEvent(QPaintEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
private:
	QTransform t_device2func;
	QTransform t_func2device;
	float pointSize = 700.0f;
	std::unique_ptr<TransferFuncProperty> funcProperty;
};
