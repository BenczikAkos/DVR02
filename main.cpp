#pragma once

#include "mainwindow.h"
#include "volumerenderwidget.h"
#include "qmainwindow.h"
/*
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>*/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
