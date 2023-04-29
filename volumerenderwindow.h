
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

protected:
    void keyPressEvent(QKeyEvent *ev) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void rotateScene(float angle);
private:
    inline static const GLfloat vertices[] = {
        1.0f,  1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    };
    GLint m_posAttr = 0;
    GLint LocViewMatrix = 0;
    GLint LocCameraPos = 0;
    GLint LocWindowSize = 0;

    QVector3D CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
    QMatrix4x4 viewMatrix = QMatrix4x4();

    QOpenGLShaderProgram *m_program = nullptr;

    int m_xRot = 0;
    int m_yRot = 16*180;
    int m_zRot = 16*180;
    QPoint mouse_lastPos;
};

#endif // VOLUMERENDERWINDOW_H
