#include "visualizationsetting.h"

VisualizationSetting::VisualizationSetting()
{
    initializeOpenGLFunctions();
    createShaderProgram(CompositionMode::MIP, ":/vshader.glsl", ":/fshad_mip.glsl");
    createShaderProgram(CompositionMode::Average, ":/vshader.glsl", ":/fshad_avg.glsl");
    createShaderProgram(CompositionMode::Accumulate, ":/vshader.glsl", ":/fshad_accumulate.glsl");
    createShaderProgram(CompositionMode::Isosurface, ":/vshader.glsl", ":/fshad_isosurface.glsl");
    QOpenGLShaderProgram* program = modes.value(activeMode).get();
    if (!program->link()) {
        qWarning() << program->log();
    }
}

std::shared_ptr<QOpenGLShaderProgram> VisualizationSetting::getActiveProgram()
{
    return modes.value(activeMode);
}

void VisualizationSetting::setUniforms()
{
    auto program = getActiveProgram().get();
    program->setUniformValue("AABBScale", AABBScale);
    program->setUniformValue("intensityMin", intensityMin);
    program->setUniformValue("intensityMax", intensityMax);
    program->setUniformValue("stepLength", stepLength);
}

void VisualizationSetting::createShaderProgram(CompositionMode mode, const QString& vertexPath, const QString& fragmentPath)
{
    auto program = std::make_shared<QOpenGLShaderProgram>();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexPath);
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentPath);
    modes.insert(mode, program);
}

void VisualizationSetting::setAABBScaleX(float value)
{
    AABBScale.setX(value);
}

void VisualizationSetting::setAABBScaleY(float value)
{
    AABBScale.setY(value);
}

void VisualizationSetting::setAABBScaleZ(float value)
{
    AABBScale.setZ(value);
}

void VisualizationSetting::setIntensityMax(int value)
{
    intensityMax = value / 255.0f;
}

void VisualizationSetting::setIntensityMin(int value)
{
    intensityMin = value / 255.0f;
}

void VisualizationSetting::setStepLength(double value)
{
    stepLength = value;
}

void VisualizationSetting::setMode(int mode)
{
    CompositionMode _mode = static_cast<CompositionMode>(mode);
    activeMode = _mode;
}