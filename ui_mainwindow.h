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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "volumerenderwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    VolumeRenderWidget *openGLWidget;
    QTabWidget *tabWidget;
    QWidget *tab_input;
    QSpinBox *datasetSize_x;
    QSpinBox *datasetSize_z;
    QLabel *TextureZSizeLabel;
    QPushButton *loadVolumeButton;
    QCheckBox *precomputeGradientsCheckBox;
    QLabel *TextureYSizeLabel;
    QSpinBox *datasetSize_y;
    QLabel *TextureXSizeLabel;
    QComboBox *dataTypeComboBox;
    QLabel *label;
    QCheckBox *littleEndianCheckBox;
    QWidget *tab_vis;
    QSlider *AABBScale_z;
    QSlider *AABBScale_y;
    QSlider *AABBScale_x;
    QLabel *modeLabel;
    QSpinBox *maxValueSpinbox;
    QLabel *MinimumValueLabel;
    QComboBox *modeComboBox;
    QSlider *intensityMaxSlider;
    QLabel *stepLengthLabel;
    QSlider *intensityMinSlider;
    QLabel *MaximumValueLabel;
    QSpinBox *minValueSpinbox;
    QDoubleSpinBox *stepLengthSpinBox;
    QPushButton *chartButton;
    QPushButton *transferFunctionButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(909, 639);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8("C:/Users/\303\201kos/Downloads/cube.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        openGLWidget = new VolumeRenderWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(openGLWidget, 0, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tab_input = new QWidget();
        tab_input->setObjectName(QString::fromUtf8("tab_input"));
        datasetSize_x = new QSpinBox(tab_input);
        datasetSize_x->setObjectName(QString::fromUtf8("datasetSize_x"));
        datasetSize_x->setGeometry(QRect(90, 30, 31, 21));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(datasetSize_x->sizePolicy().hasHeightForWidth());
        datasetSize_x->setSizePolicy(sizePolicy2);
        datasetSize_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_x->setMaximum(1024);
        datasetSize_x->setValue(256);
        datasetSize_z = new QSpinBox(tab_input);
        datasetSize_z->setObjectName(QString::fromUtf8("datasetSize_z"));
        datasetSize_z->setGeometry(QRect(90, 90, 31, 21));
        datasetSize_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_z->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_z->setMinimum(1);
        datasetSize_z->setMaximum(1024);
        datasetSize_z->setValue(256);
        TextureZSizeLabel = new QLabel(tab_input);
        TextureZSizeLabel->setObjectName(QString::fromUtf8("TextureZSizeLabel"));
        TextureZSizeLabel->setGeometry(QRect(10, 90, 72, 16));
        loadVolumeButton = new QPushButton(tab_input);
        loadVolumeButton->setObjectName(QString::fromUtf8("loadVolumeButton"));
        loadVolumeButton->setGeometry(QRect(10, 120, 171, 24));
        precomputeGradientsCheckBox = new QCheckBox(tab_input);
        precomputeGradientsCheckBox->setObjectName(QString::fromUtf8("precomputeGradientsCheckBox"));
        precomputeGradientsCheckBox->setGeometry(QRect(10, 200, 140, 20));
        precomputeGradientsCheckBox->setTristate(false);
        TextureYSizeLabel = new QLabel(tab_input);
        TextureYSizeLabel->setObjectName(QString::fromUtf8("TextureYSizeLabel"));
        TextureYSizeLabel->setGeometry(QRect(10, 60, 72, 16));
        datasetSize_y = new QSpinBox(tab_input);
        datasetSize_y->setObjectName(QString::fromUtf8("datasetSize_y"));
        datasetSize_y->setGeometry(QRect(90, 60, 31, 21));
        datasetSize_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_y->setMaximum(1024);
        datasetSize_y->setValue(256);
        TextureXSizeLabel = new QLabel(tab_input);
        TextureXSizeLabel->setObjectName(QString::fromUtf8("TextureXSizeLabel"));
        TextureXSizeLabel->setGeometry(QRect(10, 30, 72, 16));
        dataTypeComboBox = new QComboBox(tab_input);
        dataTypeComboBox->setObjectName(QString::fromUtf8("dataTypeComboBox"));
        dataTypeComboBox->setGeometry(QRect(90, 160, 91, 22));
        label = new QLabel(tab_input);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 160, 71, 21));
        littleEndianCheckBox = new QCheckBox(tab_input);
        littleEndianCheckBox->setObjectName(QString::fromUtf8("littleEndianCheckBox"));
        littleEndianCheckBox->setGeometry(QRect(10, 220, 91, 20));
        tabWidget->addTab(tab_input, QString());
        tab_vis = new QWidget();
        tab_vis->setObjectName(QString::fromUtf8("tab_vis"));
        AABBScale_z = new QSlider(tab_vis);
        AABBScale_z->setObjectName(QString::fromUtf8("AABBScale_z"));
        AABBScale_z->setGeometry(QRect(80, 30, 18, 160));
        AABBScale_z->setMinimum(1);
        AABBScale_z->setMaximum(300);
        AABBScale_z->setValue(300);
        AABBScale_z->setOrientation(Qt::Vertical);
        AABBScale_y = new QSlider(tab_vis);
        AABBScale_y->setObjectName(QString::fromUtf8("AABBScale_y"));
        AABBScale_y->setGeometry(QRect(50, 30, 18, 160));
        AABBScale_y->setMinimum(1);
        AABBScale_y->setMaximum(300);
        AABBScale_y->setSingleStep(1);
        AABBScale_y->setValue(300);
        AABBScale_y->setOrientation(Qt::Vertical);
        AABBScale_x = new QSlider(tab_vis);
        AABBScale_x->setObjectName(QString::fromUtf8("AABBScale_x"));
        AABBScale_x->setGeometry(QRect(20, 30, 18, 160));
        AABBScale_x->setMinimum(1);
        AABBScale_x->setMaximum(300);
        AABBScale_x->setValue(300);
        AABBScale_x->setOrientation(Qt::Vertical);
        modeLabel = new QLabel(tab_vis);
        modeLabel->setObjectName(QString::fromUtf8("modeLabel"));
        modeLabel->setGeometry(QRect(30, 340, 49, 16));
        maxValueSpinbox = new QSpinBox(tab_vis);
        maxValueSpinbox->setObjectName(QString::fromUtf8("maxValueSpinbox"));
        maxValueSpinbox->setGeometry(QRect(140, 290, 42, 22));
        maxValueSpinbox->setMinimum(1);
        maxValueSpinbox->setMaximum(255);
        maxValueSpinbox->setValue(255);
        MinimumValueLabel = new QLabel(tab_vis);
        MinimumValueLabel->setObjectName(QString::fromUtf8("MinimumValueLabel"));
        MinimumValueLabel->setGeometry(QRect(0, 210, 91, 21));
        modeComboBox = new QComboBox(tab_vis);
        modeComboBox->setObjectName(QString::fromUtf8("modeComboBox"));
        modeComboBox->setGeometry(QRect(70, 340, 111, 22));
        intensityMaxSlider = new QSlider(tab_vis);
        intensityMaxSlider->setObjectName(QString::fromUtf8("intensityMaxSlider"));
        intensityMaxSlider->setGeometry(QRect(10, 290, 120, 20));
        intensityMaxSlider->setMinimum(1);
        intensityMaxSlider->setMaximum(255);
        intensityMaxSlider->setValue(255);
        intensityMaxSlider->setOrientation(Qt::Horizontal);
        stepLengthLabel = new QLabel(tab_vis);
        stepLengthLabel->setObjectName(QString::fromUtf8("stepLengthLabel"));
        stepLengthLabel->setGeometry(QRect(110, 40, 71, 16));
        intensityMinSlider = new QSlider(tab_vis);
        intensityMinSlider->setObjectName(QString::fromUtf8("intensityMinSlider"));
        intensityMinSlider->setGeometry(QRect(10, 240, 120, 18));
        intensityMinSlider->setMinimum(1);
        intensityMinSlider->setMaximum(255);
        intensityMinSlider->setOrientation(Qt::Horizontal);
        MaximumValueLabel = new QLabel(tab_vis);
        MaximumValueLabel->setObjectName(QString::fromUtf8("MaximumValueLabel"));
        MaximumValueLabel->setGeometry(QRect(0, 270, 101, 16));
        minValueSpinbox = new QSpinBox(tab_vis);
        minValueSpinbox->setObjectName(QString::fromUtf8("minValueSpinbox"));
        minValueSpinbox->setGeometry(QRect(140, 240, 42, 22));
        minValueSpinbox->setMinimum(1);
        minValueSpinbox->setMaximum(255);
        stepLengthSpinBox = new QDoubleSpinBox(tab_vis);
        stepLengthSpinBox->setObjectName(QString::fromUtf8("stepLengthSpinBox"));
        stepLengthSpinBox->setGeometry(QRect(110, 60, 61, 22));
        stepLengthSpinBox->setDecimals(4);
        stepLengthSpinBox->setMinimum(0.000000000000000);
        stepLengthSpinBox->setMaximum(1.000000000000000);
        stepLengthSpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
        stepLengthSpinBox->setValue(0.001000000000000);
        chartButton = new QPushButton(tab_vis);
        chartButton->setObjectName(QString::fromUtf8("chartButton"));
        chartButton->setGeometry(QRect(60, 400, 75, 24));
        transferFunctionButton = new QPushButton(tab_vis);
        transferFunctionButton->setObjectName(QString::fromUtf8("transferFunctionButton"));
        transferFunctionButton->setGeometry(QRect(20, 430, 141, 24));
        tabWidget->addTab(tab_vis, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 909, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Volume render", nullptr));
        TextureZSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture Z size", nullptr));
        loadVolumeButton->setText(QCoreApplication::translate("MainWindow", "Load volume", nullptr));
        precomputeGradientsCheckBox->setText(QCoreApplication::translate("MainWindow", "Precompute gradients", nullptr));
        TextureYSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture Y size", nullptr));
        TextureXSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture X size", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Data type", nullptr));
        littleEndianCheckBox->setText(QCoreApplication::translate("MainWindow", "Little endian", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_input), QCoreApplication::translate("MainWindow", "Read settings", nullptr));
        modeLabel->setText(QCoreApplication::translate("MainWindow", "Mode:", nullptr));
        MinimumValueLabel->setText(QCoreApplication::translate("MainWindow", "Minimum value", nullptr));
        stepLengthLabel->setText(QCoreApplication::translate("MainWindow", "Step length", nullptr));
        MaximumValueLabel->setText(QCoreApplication::translate("MainWindow", "Maximum value", nullptr));
        chartButton->setText(QCoreApplication::translate("MainWindow", "Show chart", nullptr));
        transferFunctionButton->setText(QCoreApplication::translate("MainWindow", "Edit Transfer Function", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_vis), QCoreApplication::translate("MainWindow", "Visualization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
