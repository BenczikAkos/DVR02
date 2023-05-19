#include "mainwindow.h"
#include "volumerenderwidget.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent }
{
    canvas = new VolumeRenderWidget(this);
    setCentralWidget(canvas);
    resize(780, 560);
}

MainWindow::~MainWindow()
{
}
