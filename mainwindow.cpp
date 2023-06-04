#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qstatusbar.h"
#include "QtCore/QTime"
#include "chartdialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent },
    ui {new Ui::MainWindow}
{
    ui->setupUi(this);
    qWarning() << this;
    updateFrameRateTimer.setRemainingTime(100);
    //resize(880, 580);
    QObject::connect(this, SIGNAL(AABBChangedX(float)), ui->openGLWidget, SLOT(setAABBScaleX(float)));
    QObject::connect(this, SIGNAL(AABBChangedY(float)), ui->openGLWidget, SLOT(setAABBScaleY(float)));
    QObject::connect(this, SIGNAL(AABBChangedZ(float)), ui->openGLWidget, SLOT(setAABBScaleZ(float)));
    
    QObject::connect(this, SIGNAL(intensityMaxChanged(int)), ui->openGLWidget, SLOT(setIntensityMax(int)));
    QObject::connect(this, SIGNAL(intensityMaxChanged(int)), ui->maxValueSpinbox, SLOT(setValue(int)));
    QObject::connect(ui->maxValueSpinbox, SIGNAL(valueChanged(int)), ui->intensityMaxSlider, SLOT(setValue(int)));

    QObject::connect(this, SIGNAL(intensityMinChanged(int)), ui->openGLWidget, SLOT(setIntensityMin(int)));
    QObject::connect(this, SIGNAL(intensityMinChanged(int)), ui->minValueSpinbox, SLOT(setValue(int)));
    QObject::connect(ui->minValueSpinbox, SIGNAL(valueChanged(int)), ui->intensityMinSlider, SLOT(setValue(int)));

}

void MainWindow::paintEvent(QPaintEvent* event) {
    int thisPaint = QTime::currentTime().msecsSinceStartOfDay();
    if (updateFrameRateTimer.hasExpired()) {
        int diff = thisPaint - lastPaint;
        QStatusBar* StatusBar = statusBar();
        if (StatusBar != nullptr && diff != 0) {
            StatusBar->clearMessage();
            StatusBar->showMessage(QString("Elapsed time: %1 ms FPS: %2").arg(QString::number(diff), QString::number(1000/diff)));
        }
        updateFrameRateTimer.setRemainingTime(300);
    }
    lastPaint = thisPaint;
    update();
}

QVector3D MainWindow::getDataSizes() const
{
    auto x = ui->datasetSize_x->value();
    auto y = ui->datasetSize_y->value();
    auto z = ui->datasetSize_z->value();
    return QVector3D(x, y, z);
}

QChart* MainWindow::generateChart() const
{
    return ui->openGLWidget->generateChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadVolumeButton_clicked(bool checked)
{
    ui->openGLWidget->openFile();
}

void MainWindow::on_chartButton_clicked(bool checked)
{
    auto graphDialog = new ChartDialog(this);
    graphDialog->show();
    graphDialog->raise();
}

void MainWindow::on_AABBScale_x_valueChanged(int value)
{
    float normValue = normalizeSliderValue(*ui->AABBScale_x, value); 
    emit AABBChangedX(normValue); 
}

void MainWindow::on_AABBScale_y_valueChanged(int value) 
{ 
    float normValue = normalizeSliderValue(*ui->AABBScale_y, value); 
    emit AABBChangedY(normValue); 
}

void MainWindow::on_AABBScale_z_valueChanged(int value) 
{ 
    float normValue = normalizeSliderValue(*ui->AABBScale_z, value); 
    emit AABBChangedZ(normValue); 
}

float MainWindow::normalizeSliderValue(const QSlider& slider, int value) const
{
    int minValue = slider.minimum();
    int maxValue = slider.maximum();
    return (static_cast<float>(value)) / (maxValue - minValue);

}