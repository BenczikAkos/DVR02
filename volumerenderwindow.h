
#ifndef VOLUMERENDERWINDOW_H
#define VOLUMERENDERWINDOW_H

#include "openglwindow.h"
#include <QOpenGLShaderProgram>


class VolumeRenderWindow : public OpenGLWindow
{
public:
    using OpenGLWindow::OpenGLWindow;

    void initialize() override;
    void render() override;

private:
    GLint m_posAttr = 0;
    GLint m_matrixUniform = 0;
    GLint LocCameraPos = 0;
    GLint LocWindowSize = 0;

    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
};

#endif // VOLUMERENDERWINDOW_H
