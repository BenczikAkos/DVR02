#ifndef VOLUMERENDERWIDGET_H
#define VOLUMERENDERWIDGET_H

#include "QtOpenGLWidgets/qopenglwidget.h"
#include <qopenglextrafunctions.h>
#include <QtOpenGL/QOpenGLShaderProgram>
#include "openglwindow.h"


class VolumeRenderWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit VolumeRenderWidget(QWidget* parent = nullptr);
    ~VolumeRenderWidget();

    void initializeGL() override;
    void paintGL() override;

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
    QByteArray VolumeData = QByteArray();

    QOpenGLShaderProgram *m_program = nullptr;

    float xRot = 0;
    float yRot = 16*180;
    float zRot = 16*180;
    float aroundAngle = 0;
    QPoint mouse_lastPos;
    QVector3D camera_lastPos = QVector3D(0.0f, 0.0f, -3.0f);
};

#endif //VOLUMERENDERWIDGET_H
