#pragma once

#include <qopenglextrafunctions.h>
#include "compositionmode.h"
#include "transferfuncproperty.h"
#include <QtOpenGL/QOpenGLShaderProgram>

class VisualizationSetting : protected QOpenGLExtraFunctions
{
public:
	explicit VisualizationSetting();

public slots:
/*
    void setAABBScaleX(float value);
    void setAABBScaleY(float value);
    void setAABBScaleZ(float value);
    void setIntensityMax(int value);
    void setIntensityMin(int value);
    void setStepLength(double value);
*/
    void setMode(int mode);

private:
    CompositionMode activeMode = CompositionMode::MIP;
    QMap<CompositionMode, std::shared_ptr<QOpenGLShaderProgram>> modes;

    void createShaderProgram(CompositionMode mode, const QString& vertexPath, const QString& fragmentPath);
/* ezeket majd lehet kiszervezem egy vmi viewport osztalyba
    QVector3D CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
    QMatrix4x4 ViewMatrix = QMatrix4x4();
    QVector3D AABBScale = QVector3D(1.0f, 1.0f, 1.0f);
    float intensityMin = 0.0;
    float intensityMax = 1.0;
    float stepLength = 0.001f;

    std::shared_ptr<VolumeData> volume = nullptr;

    float xRot = 180.0f;
    float yRot = 180.0f;
    float zRot = 180.0f;
    float phi = (float)-M_PI_2;
    float elevation = 0.0f;*/
};
