#pragma once

#include "../include/mainwindow.h"
#include "../include/volumerenderwidget.h"
#include "qmainwindow.h"
#include "qapplication.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowState(Qt::WindowMaximized);
    window.show();

	return app.exec();
}
