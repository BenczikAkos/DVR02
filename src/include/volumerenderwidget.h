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
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void setRotation(float& changeable, float angle);
    void rotateScene(float phi, float theta);


private:
    QVector<GLfloat> quadVertices = {
        1.0f,  1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, 1.0f
    };
    QVector<uint> quadIndices = {
        0,1,2,
        2,3,0
    };

    //uniform locations
    GLuint m_posAttr = 0;
    GLuint BoundingEBO = 0;
    GLuint QuadEBO = 0;
    //uniforms
    QVector3D CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
    QMatrix4x4 ViewMatrix = QMatrix4x4();
    QSize windowSize;

    std::shared_ptr<VolumeData> volume = nullptr;
    std::shared_ptr<VisualizationSetting> visualizationSetting = nullptr;
    std::shared_ptr<BoundingGeometry> boundingGeometry;
    GLuint enterFBO, exitFBO = 0;
    GLuint enterTexture, exitTexture = 0;
    MainWindow* mainWindow = nullptr;
    //for display purposes
    boolean MouseFirstPressed = true;
    float xRot = 180.0f;
    float yRot = 180.0f;
    float zRot = 180.0f;
    float phi = (float)-M_PI_2;
    float elevation = 0.0f;
    float distance = 3.0f;
    QPoint mouse_lastPos = QPoint(0.0f, 0.0f);
    //functions
    void drawQuad();
    void drawBoundingGeometry();
    void normalizeAngle(float& angle);
    float fromRadian(float angle);
    void updateViewMatrix();
    void generateFBO(GLuint& fbo, GLuint& tex);
};