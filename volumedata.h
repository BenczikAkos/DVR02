#pragma once
#include "QtOpenGLWidgets/qopenglwidget.h"
#include "mainwindow.h"
#include <qopenglextrafunctions.h>


class VolumeData : protected QOpenGLExtraFunctions
{
public:
	explicit VolumeData();
	VolumeData(GLuint loc, MainWindow* _mainWindow);
	void loadVolume(QString path);
	QChart* createChart() const;
	const void bind();
private:
	void uploadTexture();
	MainWindow* mainWindow;
	GLuint location = 0;
	QByteArray data = QByteArray();

};

