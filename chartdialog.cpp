#include "chartdialog.h"
#include "ui_chartdialog.h"

//#include "qchart.h"

ChartDialog::ChartDialog(MainWindow* parent)
	: QDialog { parent },
	ui {new Ui::ChartDialog}
{
	ui->setupUi(this);
	QChart* chart = parent->generateChart();
	ui->chart->setChart(chart);
}
