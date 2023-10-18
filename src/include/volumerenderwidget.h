#pragma once

#include "QtOpenGLWidgets/qopenglwidget.h"
#include "QtWidgets/qfiledialog.h"
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include "volumedata.h"
#include "visualizationsetting.h"
#include "boundinggeometry.h"

class VolumeRenderWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit VolumeRenderWidget(QWidget* parent = nullptr);

    void initializeGL() override;
    void paintGL() override;
    void openFile();
    void setVisualizationSetting(std::shared_ptr<VisualizationSetting> _visualizationSetting) { visualizationSetting = _visualizationSetting; }
    QChart* generateChart() const;

protected:
    void keyPressEvent(QKeyEvent *ev) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void setRotation(float& changeable, float angle);
    void rotateScene(float phi, float theta);


private:
    //inline static const GLfloat quadVertices[] = {
    //    1.0f,  1.0f,
    //    1.0f, -1.0f,
    //    -1.0f, -1.0f,
    //    -1.0f, 1.0f
    //};
    //QVector<uint> quadIndices = {
    //    0,1,2,
    //    2,3,0
    //};
    inline static const GLfloat quadVertices[] = {
        0.0f, 0.0f, 0.0f, // 0
        1.0f, 0.0f, 0.0f, // 1
        1.0f, 1.0f, 0.0f, // 2
        0.0f, 1.0f, 0.0f, // 3
        0.0f, 0.0f, 1.0f, // 4
        1.0f, 0.0f, 1.0f, // 5
        1.0f, 1.0f, 1.0f, // 6
        0.0f, 1.0f, 1.0f  // 7
    };
    QVector<uint> quadIndices = {
        0, 1, 2,  // Front
        2, 3, 0,
        1, 5, 6,  // Right
        6, 2, 1,
        7, 6, 5,  // Top
        5, 4, 7,
        4, 0, 3,  // Left
        3, 7, 4,
        4, 5, 1,  // Bottom
        1, 0, 4,
        3, 2, 6,  // Back
        6, 7, 3
    };
    //uniform locations
    GLuint m_posAttr = 0;
    GLuint EBO = 0;
    //uniforms
    QVector3D CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
    QMatrix4x4 ViewMatrix = QMatrix4x4();
    QSize windowSize;

    std::shared_ptr<VolumeData> volume = nullptr;
    std::shared_ptr<VisualizationSetting> visualizationSetting = nullptr;
    std::shared_ptr<BoundingGeometry> boundingGeometry;
    GLuint fbo = 0;
    GLuint PARCTex = 0;
    MainWindow* mainWindow = nullptr;
    //for display purposes
    boolean MouseFirstPressed = true;
    float xRot = 180.0f;
    float yRot = 180.0f;
    float zRot = 180.0f;
    float phi = (float)-M_PI_2;
    float elevation = 0.0f;
    QPoint mouse_lastPos = QPoint(0.0f, 0.0f);
    //functions
    void drawQuad();
    void drawBoundingGeometry();
    void normalizeAngle(float& angle);
    float fromRadian(float angle);
    void generateFBO();
};