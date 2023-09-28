#pragma once
#include <qwidget.h>
#include "mainwindow.h"

namespace Ui {
	class ChartDialog;
}

class ChartDialog : public QWidget
{
	Q_OBJECT
public:
	explicit ChartDialog(MainWindow* parent = nullptr);
	~ChartDialog();
	void focusOutEvent(QFocusEvent* event) override;
private:
	Ui::ChartDialog* ui;
};

