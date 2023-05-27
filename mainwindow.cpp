#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qstatusbar.h"
#include "QtCore/QTime"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent },
    ui {new Ui::MainWindow}
{
    ui->setupUi(this);
    qWarning() << this;
    updateFrameRateTimer.setRemainingTime(100);
    resize(880, 580);
    QObject::connect(this, SIGNAL(AABBChangedX(int )), ui->openGLWidget, SLOT(setAABBScaleX(int )));
    QObject::connect(this, SIGNAL(AABBChangedY(int )), ui->openGLWidget, SLOT(setAABBScaleY(int )));
    QObject::connect(this, SIGNAL(AABBChangedZ(int )), ui->openGLWidget, SLOT(setAABBScaleZ(int )));
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

void MainWindow::setBarGraph(QChart* chart)
{
    ui->barGraph->setChart(chart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadVolumeButton_clicked(bool checked)
{
    ui->openGLWidget->openFile();
}
