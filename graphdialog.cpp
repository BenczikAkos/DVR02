#include "graphdialog.h"
#include <QLineSeries>
#include <QChart>

GraphDialog::GraphDialog(const QByteArray& data)
{
    QMap<char, qreal> valueCounts;
    for (char byte : data) {
        if (byte != 0)
        {
            if (valueCounts.contains(byte)) {
                valueCounts[byte] += 1.0;
            }
            else {
                valueCounts[byte] = 1.0;
            }
        }
    }

    QLineSeries* series = new QLineSeries();
    for (int i = 0; i < valueCounts.values().size(); ++i) {
        series->append(i, valueCounts.values()[i]);
    }
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->hide();
}
