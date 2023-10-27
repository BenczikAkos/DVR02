#include "../include/visualizationsetting.h"

VisualizationSetting::VisualizationSetting()
{
	initializeOpenGLFunctions();
	createShaderProgram(CompositionMode::MIP, "src\\shaders\\vshader_quad.glsl", "src\\shaders\\fshad_mip.glsl");
	createShaderProgram(CompositionMode::Average, "src\\shaders\\vshader_quad.glsl", "src\\shaders\\fshad_avg.glsl");
	createShaderProgram(CompositionMode::Accumulate, "src\\shaders\\vshader_quad.glsl", "src\\shaders\\fshad_accumulate.glsl");
	createShaderProgram(CompositionMode::Isosurface, "src\\shaders\\vshader_quad.glsl", "src\\shaders\\fshad_isosurface.glsl");
	createShaderProgram(CompositionMode::PARCPass, "src\\shaders\\vshader_bounding.glsl", "src\\shaders\\fshad_PARC.glsl");
	QOpenGLShaderProgram* program = modes.value(activeMode).get();
	if (!program->link()) {
		qWarning() << program->log();
	}
	transferFunctions = QVector< std::shared_ptr<TransferFuncProperty >>();
	GLuint transferFuncLocation = program->uniformLocation("TransferFunction");
	//Q_ASSERT(transferFuncLocation != -1);
	transferFunctions.append(std::make_shared<TransferFuncProperty>(transferFuncLocation));
}

std::shared_ptr<QOpenGLShaderProgram> VisualizationSetting::getActiveProgram()
{
	return modes.value(activeMode);
}

std::shared_ptr<QOpenGLShaderProgram> VisualizationSetting::getPARCProgram()
{
	return modes.value(CompositionMode::PARCPass);
}

void VisualizationSetting::setUniforms()
{
	auto program = getActiveProgram().get();
	program->setUniformValue("AABBScale", AABBScale);
	program->setUniformValue("intensityMin", intensityMin);
	program->setUniformValue("intensityMax", intensityMax);
	program->setUniformValue("stepLength", stepLength);
	transferFunctions.at(0)->bind();
}

std::shared_ptr<TransferFuncProperty> VisualizationSetting::getActiveTransferFunction()
{
	return transferFunctions.at(0);
}

bool VisualizationSetting::isTransparent(int value) const
{
	return transferFunctions.at(0)->isTransparent(value, intensityMin);
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