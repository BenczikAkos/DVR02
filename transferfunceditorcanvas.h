#pragma once
#include <QWidget>
#include <QPainter>

class TransferFuncEditorCanvas : public QWidget {
	Q_OBJECT
public:
	explicit TransferFuncEditorCanvas(QWidget* parent = nullptr);
protected:
	void paintEvent(QPaintEvent* event) override;
};
