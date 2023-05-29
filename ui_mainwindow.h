/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "volumerenderwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    VolumeRenderWidget *openGLWidget;
    QSpinBox *datasetSize_x;
    QSpinBox *datasetSize_y;
    QSpinBox *datasetSize_z;
    QSlider *AABBScale_x;
    QSlider *AABBScale_y;
    QSlider *AABBScale_z;
    QChartView *barGraph;
    QPushButton *loadVolumeButton;
    QPushButton *chartButton;
    QSlider *intensityCapSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(864, 710);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new VolumeRenderWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 20, 631, 521));
        datasetSize_x = new QSpinBox(centralwidget);
        datasetSize_x->setObjectName(QString::fromUtf8("datasetSize_x"));
        datasetSize_x->setGeometry(QRect(810, 10, 51, 29));
        datasetSize_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_x->setMaximum(1024);
        datasetSize_x->setValue(256);
        datasetSize_y = new QSpinBox(centralwidget);
        datasetSize_y->setObjectName(QString::fromUtf8("datasetSize_y"));
        datasetSize_y->setGeometry(QRect(810, 50, 48, 29));
        datasetSize_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_y->setMaximum(1024);
        datasetSize_y->setValue(256);
        datasetSize_z = new QSpinBox(centralwidget);
        datasetSize_z->setObjectName(QString::fromUtf8("datasetSize_z"));
        datasetSize_z->setGeometry(QRect(810, 90, 48, 29));
        datasetSize_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_z->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_z->setMinimum(1);
        datasetSize_z->setMaximum(1024);
        datasetSize_z->setValue(256);
        AABBScale_x = new QSlider(centralwidget);
        AABBScale_x->setObjectName(QString::fromUtf8("AABBScale_x"));
        AABBScale_x->setGeometry(QRect(660, 10, 18, 160));
        AABBScale_x->setMinimum(1);
        AABBScale_x->setMaximum(300);
        AABBScale_x->setValue(300);
        AABBScale_x->setOrientation(Qt::Vertical);
        AABBScale_y = new QSlider(centralwidget);
        AABBScale_y->setObjectName(QString::fromUtf8("AABBScale_y"));
        AABBScale_y->setGeometry(QRect(690, 10, 18, 160));
        AABBScale_y->setMinimum(1);
        AABBScale_y->setMaximum(300);
        AABBScale_y->setValue(300);
        AABBScale_y->setOrientation(Qt::Vertical);
        AABBScale_z = new QSlider(centralwidget);
        AABBScale_z->setObjectName(QString::fromUtf8("AABBScale_z"));
        AABBScale_z->setGeometry(QRect(720, 10, 18, 160));
        AABBScale_z->setMinimum(1);
        AABBScale_z->setMaximum(300);
        AABBScale_z->setValue(300);
        AABBScale_z->setOrientation(Qt::Vertical);
        barGraph = new QChartView(centralwidget);
        barGraph->setObjectName(QString::fromUtf8("barGraph"));
        barGraph->setGeometry(QRect(10, 550, 631, 101));
        loadVolumeButton = new QPushButton(centralwidget);
        loadVolumeButton->setObjectName(QString::fromUtf8("loadVolumeButton"));
        loadVolumeButton->setGeometry(QRect(750, 130, 101, 24));
        chartButton = new QPushButton(centralwidget);
        chartButton->setObjectName(QString::fromUtf8("chartButton"));
        chartButton->setGeometry(QRect(750, 160, 101, 24));
        intensityCapSlider = new QSlider(centralwidget);
        intensityCapSlider->setObjectName(QString::fromUtf8("intensityCapSlider"));
        intensityCapSlider->setGeometry(QRect(660, 220, 191, 18));
        intensityCapSlider->setMinimum(1);
        intensityCapSlider->setMaximum(255);
        intensityCapSlider->setValue(255);
        intensityCapSlider->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 864, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loadVolumeButton->setText(QCoreApplication::translate("MainWindow", "Load volume", nullptr));
        chartButton->setText(QCoreApplication::translate("MainWindow", "Show chart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
