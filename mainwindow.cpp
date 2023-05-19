#include "mainwindow.h"
#include "volumerenderwidget.h"
#include "qstatusbar.h"
#include "QtCore/QTime"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent }
{
    updateFrameRateTimer.setRemainingTime(100);
    canvas = new VolumeRenderWidget(this);
    setCentralWidget(canvas);
    resize(780, 560);
}

void MainWindow::paintEvent(QPaintEvent* event) {
    int thisPaint = QTime::currentTime().msecsSinceStartOfDay();
    if (updateFrameRateTimer.hasExpired()) {
        int diff = thisPaint - lastPaint;
        QStatusBar* StatusBar = statusBar();
        if (StatusBar != nullptr) {
            StatusBar->clearMessage();
            StatusBar->showMessage(QString("Elapsed time: %1 ms FPS: %2").arg(QString::number(diff), QString::number(1000/diff)));
        }
        updateFrameRateTimer.setRemainingTime(100);
    }
    lastPaint = thisPaint;
    update();
}

MainWindow::~MainWindow()
{
}
