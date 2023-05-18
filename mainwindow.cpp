#include "mainwindow.h"
#include "volumerenderwidget.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent }
{
    VolumeRenderWidget canvas(this);
    setCentralWidget(&canvas);
}

MainWindow::~MainWindow()
{
}