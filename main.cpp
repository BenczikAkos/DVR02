#include "volumerenderwidget.h"

#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    VolumeRenderWidget window;
    window.setFormat(format);
    window.resize(640, 480);
    window.setVisible(true);

    //window.setAnimating(true);

    return app.exec();
}
