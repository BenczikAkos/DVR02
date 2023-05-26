#pragma once

#include "QtOpenGLWidgets/qopenglwidget.h"
#include "QtWidgets/qfiledialog.h"
#include <qopenglextrafunctions.h>
#include <QtOpenGL/QOpenGLShaderProgram>
#include "openglwindow.h"
#include "volumedata.h"


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
    void wheelEvent(QWheelEvent *event) override;
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void rotateScene(float phi, float theta);
private:
    inline static const GLfloat vertices[] = {
        1.0f,  1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    };
    GLuint m_posAttr = 0;
    GLuint LocViewMatrix = 0;
    GLuint LocCameraPos = 0;
    GLuint LocWindowSize = 0;
    boolean MouseFirstPressed = true;
    QOpenGLShaderProgram *m_program = nullptr;

    QVector3D CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
    QMatrix4x4 viewMatrix = QMatrix4x4();
    VolumeData *volume = nullptr;
   
    float xRot = 180;
    float yRot = 180;
    float zRot = 180;
    float phi = -M_PI_2;
    float elevation = 0.0;
    QPoint mouse_lastPos = QPoint(0.0, 0.0);
    QVector3D camera_lastPos = QVector3D(0.0f, 0.0f, -3.0f);
    void normalizeAngle(int& angle);
    float fromRadian(float angle);
};