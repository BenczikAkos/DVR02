
#ifndef VOLUMERENDERWINDOW_H
#define VOLUMERENDERWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>


class VolumeRenderWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    using QOpenGLWindow::QOpenGLWindow;

    void initializeGL() override;
    void paintGL() override;

private:
    GLint m_posAttr = 0;
    GLint m_matrixUniform = 0;
    GLint LocCameraPos = 0;
    GLint LocWindowSize = 0;

    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
};

#endif // VOLUMERENDERWINDOW_H
