#pragma once
#include <QWidget>
#include <QPainter>
#include "transferfuncproperty.h"

class TransferFuncEditorCanvas : public QWidget {
	Q_OBJECT
public:
	explicit TransferFuncEditorCanvas(QWidget* parent = nullptr);
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	float pointSize = 700.0f;
	std::unique_ptr<TransferFuncProperty> funcProperty;
};
