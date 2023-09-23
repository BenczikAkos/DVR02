#pragma once
#include "QtOpenGLWidgets/qopenglwidget.h"
#include "mainwindow.h"
#include <qopenglextrafunctions.h>


class VolumeData : protected QOpenGLExtraFunctions
{
public:
	explicit VolumeData();
	VolumeData(GLuint loc, MainWindow* _mainWindow);
	void loadVolume(QString path, boolean precompute_grads, GLenum dataType);
	QChart* createChart() const;
	const void bind();
private:
	void uploadTexture(boolean precompute_grads, GLenum dataType);
	char computeGrad(const int position, const QByteArray& values, const int stepsize);
	MainWindow* mainWindow;
	GLuint location = 0;
	QByteArray data = QByteArray();

};

