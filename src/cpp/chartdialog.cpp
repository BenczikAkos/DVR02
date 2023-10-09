#include "../include/chartdialog.h"
#include "../include/ui_chartdialog.h"


ChartDialog::ChartDialog(MainWindow* parent)
	: QWidget(parent, Qt::Window) ,
	ui {new Ui::ChartDialog}
{
	ui->setupUi(this);
	QChart* chart = parent->generateChart();
	ui->chart->setChart(chart);
}

ChartDialog::~ChartDialog()
{
	delete ui;
}

void ChartDialog::focusOutEvent(QFocusEvent* event)
{
	Q_UNUSED(event)
	showMinimized();
}
