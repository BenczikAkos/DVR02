/********************************************************************************
** Form generated from reading UI file 'chartdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARTDIALOG_H
#define UI_CHARTDIALOG_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QChartView *chart;

    void setupUi(QDialog *ChartDialog)
    {
        if (ChartDialog->objectName().isEmpty())
            ChartDialog->setObjectName(QString::fromUtf8("ChartDialog"));
        ChartDialog->resize(1155, 300);
        verticalLayoutWidget = new QWidget(ChartDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1161, 301));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chart = new QChartView(verticalLayoutWidget);
        chart->setObjectName(QString::fromUtf8("chart"));

        verticalLayout->addWidget(chart);


        retranslateUi(ChartDialog);

        QMetaObject::connectSlotsByName(ChartDialog);
    } // setupUi

    void retranslateUi(QDialog *ChartDialog)
    {
        ChartDialog->setWindowTitle(QCoreApplication::translate("ChartDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChartDialog: public Ui_ChartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTDIALOG_H
