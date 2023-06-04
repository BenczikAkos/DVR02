/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
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
    QPushButton *loadVolumeButton;
    QPushButton *chartButton;
    QSlider *intensityMaxSlider;
    QSlider *intensityMinSlider;
    QLabel *TextureXSizeLabel;
    QLabel *TextureYSizeLabel;
    QLabel *TextureZSizeLabel;
    QLabel *MinimumValueLabel;
    QLabel *MaximumValueLabel;
    QSpinBox *minValueSpinbox;
    QSpinBox *maxValueSpinbox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(917, 602);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new VolumeRenderWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 20, 631, 521));
        datasetSize_x = new QSpinBox(centralwidget);
        datasetSize_x->setObjectName(QString::fromUtf8("datasetSize_x"));
        datasetSize_x->setGeometry(QRect(850, 10, 51, 29));
        datasetSize_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_x->setMaximum(1024);
        datasetSize_x->setValue(256);
        datasetSize_y = new QSpinBox(centralwidget);
        datasetSize_y->setObjectName(QString::fromUtf8("datasetSize_y"));
        datasetSize_y->setGeometry(QRect(850, 50, 48, 29));
        datasetSize_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_y->setMaximum(1024);
        datasetSize_y->setValue(256);
        datasetSize_z = new QSpinBox(centralwidget);
        datasetSize_z->setObjectName(QString::fromUtf8("datasetSize_z"));
        datasetSize_z->setGeometry(QRect(850, 90, 48, 29));
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
        loadVolumeButton = new QPushButton(centralwidget);
        loadVolumeButton->setObjectName(QString::fromUtf8("loadVolumeButton"));
        loadVolumeButton->setGeometry(QRect(800, 130, 101, 24));
        chartButton = new QPushButton(centralwidget);
        chartButton->setObjectName(QString::fromUtf8("chartButton"));
        chartButton->setGeometry(QRect(800, 160, 101, 24));
        intensityMaxSlider = new QSlider(centralwidget);
        intensityMaxSlider->setObjectName(QString::fromUtf8("intensityMaxSlider"));
        intensityMaxSlider->setGeometry(QRect(660, 290, 191, 18));
        intensityMaxSlider->setMinimum(1);
        intensityMaxSlider->setMaximum(255);
        intensityMaxSlider->setValue(255);
        intensityMaxSlider->setOrientation(Qt::Horizontal);
        intensityMinSlider = new QSlider(centralwidget);
        intensityMinSlider->setObjectName(QString::fromUtf8("intensityMinSlider"));
        intensityMinSlider->setGeometry(QRect(660, 240, 191, 18));
        intensityMinSlider->setMinimum(1);
        intensityMinSlider->setMaximum(255);
        intensityMinSlider->setOrientation(Qt::Horizontal);
        TextureXSizeLabel = new QLabel(centralwidget);
        TextureXSizeLabel->setObjectName(QString::fromUtf8("TextureXSizeLabel"));
        TextureXSizeLabel->setGeometry(QRect(770, 20, 91, 16));
        TextureYSizeLabel = new QLabel(centralwidget);
        TextureYSizeLabel->setObjectName(QString::fromUtf8("TextureYSizeLabel"));
        TextureYSizeLabel->setGeometry(QRect(770, 60, 91, 16));
        TextureZSizeLabel = new QLabel(centralwidget);
        TextureZSizeLabel->setObjectName(QString::fromUtf8("TextureZSizeLabel"));
        TextureZSizeLabel->setGeometry(QRect(770, 100, 91, 16));
        MinimumValueLabel = new QLabel(centralwidget);
        MinimumValueLabel->setObjectName(QString::fromUtf8("MinimumValueLabel"));
        MinimumValueLabel->setGeometry(QRect(650, 210, 91, 21));
        MaximumValueLabel = new QLabel(centralwidget);
        MaximumValueLabel->setObjectName(QString::fromUtf8("MaximumValueLabel"));
        MaximumValueLabel->setGeometry(QRect(650, 270, 101, 16));
        minValueSpinbox = new QSpinBox(centralwidget);
        minValueSpinbox->setObjectName(QString::fromUtf8("minValueSpinbox"));
        minValueSpinbox->setGeometry(QRect(860, 240, 42, 22));
        minValueSpinbox->setMinimum(1);
        minValueSpinbox->setMaximum(255);
        maxValueSpinbox = new QSpinBox(centralwidget);
        maxValueSpinbox->setObjectName(QString::fromUtf8("maxValueSpinbox"));
        maxValueSpinbox->setGeometry(QRect(860, 290, 42, 22));
        maxValueSpinbox->setMinimum(1);
        maxValueSpinbox->setMaximum(255);
        maxValueSpinbox->setValue(255);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 917, 22));
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
        TextureXSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture X size", nullptr));
        TextureYSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture Y size", nullptr));
        TextureZSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture Z size", nullptr));
        MinimumValueLabel->setText(QCoreApplication::translate("MainWindow", "Minimum value", nullptr));
        MaximumValueLabel->setText(QCoreApplication::translate("MainWindow", "Maximum value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
