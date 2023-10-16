#pragma once

#include <qopenglextrafunctions.h>
#include "compositionmode.h"
#include "transferfuncproperty.h"
#include <QtOpenGL/QOpenGLShaderProgram>

class VisualizationSetting : public QObject, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
	explicit VisualizationSetting();
    std::shared_ptr<QOpenGLShaderProgram> getActiveProgram();
    std::shared_ptr<QOpenGLShaderProgram> getPARCProgram();
    void setUniforms();
    std::shared_ptr<TransferFuncProperty> getActiveTransferFunction();
    bool isTransparent(int value) const;
public slots:
    void setAABBScaleX(float value);
    void setAABBScaleY(float value);
    void setAABBScaleZ(float value);
    void setIntensityMax(int value);
    void setIntensityMin(int value);
    void setStepLength(double value);
    void setMode(int mode);

private:
    CompositionMode activeMode = CompositionMode::MIP;
    QMap<CompositionMode, std::shared_ptr<QOpenGLShaderProgram>> modes;
    QVector<std::shared_ptr<TransferFuncProperty>> transferFunctions;

    void createShaderProgram(CompositionMode mode, const QString& vertexPath, const QString& fragmentPath);
    QVector3D AABBScale = QVector3D(1.0f, 1.0f, 1.0f);
    float intensityMin = 0.0;
    float intensityMax = 1.0;
    float stepLength = 0.001f;
};
