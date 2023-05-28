#pragma once
#include <qdialog.h>
#include "mainwindow.h"

namespace Ui {
	class ChartDialog;
}

class ChartDialog : public QDialog
{
	Q_OBJECT
public:
	explicit ChartDialog(MainWindow* parent = nullptr);
private:
	Ui::ChartDialog* ui;
};

