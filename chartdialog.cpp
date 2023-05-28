#include "chartdialog.h"
#include "ui_chartdialog.h"


ChartDialog::ChartDialog(MainWindow* parent)
	: QWidget(parent, Qt::Window) ,
	ui {new Ui::ChartDialog}
{
	ui->setupUi(this);
	QChart* chart = parent->generateChart();
	ui->chart->setChart(chart);
	//setWindowFlags(Qt::Tool | Qt::WindowStaysOnBottomHint);
	setFocusPolicy(Qt::TabFocus);
}

void ChartDialog::focusOutEvent(QFocusEvent* event)
{
	showMinimized();
}
