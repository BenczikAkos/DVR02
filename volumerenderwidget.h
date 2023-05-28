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
    void openFile();
    QChart* generateChart() const;

protected:
    void keyPressEvent(QKeyEvent *ev) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void setRotation(float angle, float& changeable);
    void rotateScene(float phi, float theta);

public slots:
    void setAABBScaleX(int value);
    void setAABBScaleY(int value);
    void setAABBScaleZ(int value);

private:
    inline static const GLfloat vertices[] = {
        1.0f,  1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    };
    QOpenGLShaderProgram *m_program = nullptr;
    boolean MouseFirstPressed = true;
    //uniform locations
    GLuint m_posAttr = 0;
    //uniforms
    QVector3D CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
    QMatrix4x4 ViewMatrix = QMatrix4x4();
    QVector3D AABBScale = QVector3D(1.0f, 1.0f, 1.0f);

    VolumeData *volume = nullptr;
   
    float xRot = 180;
    float yRot = 180;
    float zRot = 180;
    float phi = -M_PI_2;
    float elevation = 0.0;
    QPoint mouse_lastPos = QPoint(0.0, 0.0);
    void normalizeAngle(float& angle);
    float fromRadian(float angle);
};