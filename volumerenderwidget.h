#pragma once

#include "QtOpenGLWidgets/qopenglwidget.h"
#include "QtWidgets/qfiledialog.h"
#include <qopenglextrafunctions.h>
#include <QtOpenGL/QOpenGLShaderProgram>
#include "openglwindow.h"
#include "volumedata.h"

enum class Mode {
    MIP = 0,
    Accumulate = 1,
    Average = 2,
};

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
    void setRotation(float& changeable, float angle);
    void rotateScene(float phi, float theta);

public slots:
    void setAABBScaleX(float value);
    void setAABBScaleY(float value);
    void setAABBScaleZ(float value);
    void setIntensityMax(int value);
    void setIntensityMin(int value);
    void setStepLength(double value);
    void setMode(int mode);

private:
    inline static const GLfloat vertices[] = {
        1.0f,  1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    };
    //QOpenGLShaderProgram *m_program = nullptr;
    Mode activeMode = Mode::MIP;  
    QMap<Mode, QOpenGLShaderProgram*> modes;
    //uniform locations
    GLuint m_posAttr = 0;
    //uniforms
    QVector3D CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
    QMatrix4x4 ViewMatrix = QMatrix4x4();
    QVector3D AABBScale = QVector3D(1.0f, 1.0f, 1.0f);
    float intensityMin = 0.0;
    float intensityMax = 1.0;
    float stepLength = 0.001;

    VolumeData *volume = nullptr;
    //for display purposes
    boolean MouseFirstPressed = true;
    float xRot = 180;
    float yRot = 180;
    float zRot = 180;
    float phi = -M_PI_2;
    float elevation = 0.0;
    QPoint mouse_lastPos = QPoint(0.0, 0.0);
    void normalizeAngle(float& angle);
    float fromRadian(float angle);
};