
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
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void loadVolume(QString path);
    void generateTexture(const char* data);
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
    GLuint LocVolumeSampler = 0;
    boolean MouseFirstPressed = true;

    QVector3D CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
    QMatrix4x4 viewMatrix = QMatrix4x4();

    QOpenGLShaderProgram *m_program = nullptr;

    float xRot = 0;
    float yRot = 16*180;
    float zRot = 16*180;
    float aroundAngle = 0;
    QPoint mouse_lastPos;
    QVector3D camera_lastPos = QVector3D(0.0f, 0.0f, -3.0f);
};

#endif // VOLUMERENDERWINDOW_H
