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
    VolumeRenderWidget *openGLWidget;
    QPushButton *chartButton;
    QTabWidget *tabWidget;
    QWidget *tab_input;
    QCheckBox *precomputeGradientsCheckBox;
    QLabel *TextureZSizeLabel;
    QSpinBox *datasetSize_y;
    QLabel *TextureXSizeLabel;
    QSpinBox *datasetSize_x;
    QLabel *TextureYSizeLabel;
    QPushButton *loadVolumeButton;
    QSpinBox *datasetSize_z;
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
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(919, 604);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("Default");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("C:/Users/\303\201kos/Downloads/cube-3d.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        openGLWidget = new VolumeRenderWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 20, 631, 521));
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        chartButton = new QPushButton(centralwidget);
        chartButton->setObjectName(QString::fromUtf8("chartButton"));
        chartButton->setGeometry(QRect(670, 530, 101, 24));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(660, 0, 261, 531));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tab_input = new QWidget();
        tab_input->setObjectName(QString::fromUtf8("tab_input"));
        precomputeGradientsCheckBox = new QCheckBox(tab_input);
        precomputeGradientsCheckBox->setObjectName(QString::fromUtf8("precomputeGradientsCheckBox"));
        precomputeGradientsCheckBox->setGeometry(QRect(0, 170, 151, 20));
        precomputeGradientsCheckBox->setTristate(false);
        TextureZSizeLabel = new QLabel(tab_input);
        TextureZSizeLabel->setObjectName(QString::fromUtf8("TextureZSizeLabel"));
        TextureZSizeLabel->setGeometry(QRect(20, 115, 91, 16));
        datasetSize_y = new QSpinBox(tab_input);
        datasetSize_y->setObjectName(QString::fromUtf8("datasetSize_y"));
        datasetSize_y->setGeometry(QRect(100, 65, 48, 29));
        datasetSize_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_y->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_y->setMaximum(1024);
        datasetSize_y->setValue(256);
        TextureXSizeLabel = new QLabel(tab_input);
        TextureXSizeLabel->setObjectName(QString::fromUtf8("TextureXSizeLabel"));
        TextureXSizeLabel->setGeometry(QRect(20, 35, 91, 16));
        datasetSize_x = new QSpinBox(tab_input);
        datasetSize_x->setObjectName(QString::fromUtf8("datasetSize_x"));
        datasetSize_x->setGeometry(QRect(100, 25, 51, 29));
        datasetSize_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_x->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_x->setMaximum(1024);
        datasetSize_x->setValue(256);
        TextureYSizeLabel = new QLabel(tab_input);
        TextureYSizeLabel->setObjectName(QString::fromUtf8("TextureYSizeLabel"));
        TextureYSizeLabel->setGeometry(QRect(20, 75, 91, 16));
        loadVolumeButton = new QPushButton(tab_input);
        loadVolumeButton->setObjectName(QString::fromUtf8("loadVolumeButton"));
        loadVolumeButton->setGeometry(QRect(50, 145, 101, 24));
        datasetSize_z = new QSpinBox(tab_input);
        datasetSize_z->setObjectName(QString::fromUtf8("datasetSize_z"));
        datasetSize_z->setGeometry(QRect(100, 105, 48, 29));
        datasetSize_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datasetSize_z->setButtonSymbols(QAbstractSpinBox::NoButtons);
        datasetSize_z->setMinimum(1);
        datasetSize_z->setMaximum(1024);
        datasetSize_z->setValue(256);
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
        modeLabel->setGeometry(QRect(80, 360, 49, 16));
        maxValueSpinbox = new QSpinBox(tab_vis);
        maxValueSpinbox->setObjectName(QString::fromUtf8("maxValueSpinbox"));
        maxValueSpinbox->setGeometry(QRect(210, 290, 42, 22));
        maxValueSpinbox->setMinimum(1);
        maxValueSpinbox->setMaximum(255);
        maxValueSpinbox->setValue(255);
        MinimumValueLabel = new QLabel(tab_vis);
        MinimumValueLabel->setObjectName(QString::fromUtf8("MinimumValueLabel"));
        MinimumValueLabel->setGeometry(QRect(0, 210, 91, 21));
        modeComboBox = new QComboBox(tab_vis);
        modeComboBox->setObjectName(QString::fromUtf8("modeComboBox"));
        modeComboBox->setGeometry(QRect(127, 360, 121, 22));
        intensityMaxSlider = new QSlider(tab_vis);
        intensityMaxSlider->setObjectName(QString::fromUtf8("intensityMaxSlider"));
        intensityMaxSlider->setGeometry(QRect(10, 290, 191, 18));
        intensityMaxSlider->setMinimum(1);
        intensityMaxSlider->setMaximum(255);
        intensityMaxSlider->setValue(255);
        intensityMaxSlider->setOrientation(Qt::Horizontal);
        stepLengthLabel = new QLabel(tab_vis);
        stepLengthLabel->setObjectName(QString::fromUtf8("stepLengthLabel"));
        stepLengthLabel->setGeometry(QRect(110, 330, 71, 16));
        intensityMinSlider = new QSlider(tab_vis);
        intensityMinSlider->setObjectName(QString::fromUtf8("intensityMinSlider"));
        intensityMinSlider->setGeometry(QRect(10, 240, 191, 18));
        intensityMinSlider->setMinimum(1);
        intensityMinSlider->setMaximum(255);
        intensityMinSlider->setOrientation(Qt::Horizontal);
        MaximumValueLabel = new QLabel(tab_vis);
        MaximumValueLabel->setObjectName(QString::fromUtf8("MaximumValueLabel"));
        MaximumValueLabel->setGeometry(QRect(0, 270, 101, 16));
        minValueSpinbox = new QSpinBox(tab_vis);
        minValueSpinbox->setObjectName(QString::fromUtf8("minValueSpinbox"));
        minValueSpinbox->setGeometry(QRect(210, 240, 42, 22));
        minValueSpinbox->setMinimum(1);
        minValueSpinbox->setMaximum(255);
        stepLengthSpinBox = new QDoubleSpinBox(tab_vis);
        stepLengthSpinBox->setObjectName(QString::fromUtf8("stepLengthSpinBox"));
        stepLengthSpinBox->setGeometry(QRect(190, 330, 62, 22));
        stepLengthSpinBox->setDecimals(4);
        stepLengthSpinBox->setMinimum(0.000000000000000);
        stepLengthSpinBox->setMaximum(1.000000000000000);
        stepLengthSpinBox->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
        stepLengthSpinBox->setValue(0.001000000000000);
        tabWidget->addTab(tab_vis, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 919, 22));
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
        chartButton->setText(QCoreApplication::translate("MainWindow", "Show chart", nullptr));
        precomputeGradientsCheckBox->setText(QCoreApplication::translate("MainWindow", "Precompute gradients", nullptr));
        TextureZSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture Z size", nullptr));
        TextureXSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture X size", nullptr));
        TextureYSizeLabel->setText(QCoreApplication::translate("MainWindow", "Texture Y size", nullptr));
        loadVolumeButton->setText(QCoreApplication::translate("MainWindow", "Load volume", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_input), QCoreApplication::translate("MainWindow", "Read settings", nullptr));
        modeLabel->setText(QCoreApplication::translate("MainWindow", "Mode:", nullptr));
        MinimumValueLabel->setText(QCoreApplication::translate("MainWindow", "Minimum value", nullptr));
        stepLengthLabel->setText(QCoreApplication::translate("MainWindow", "Step length", nullptr));
        MaximumValueLabel->setText(QCoreApplication::translate("MainWindow", "Maximum value", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_vis), QCoreApplication::translate("MainWindow", "Visualization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
