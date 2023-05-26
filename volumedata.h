#pragma once
#include "QtOpenGLWidgets/qopenglwidget.h"
#include "mainwindow.h"
#include <qopenglextrafunctions.h>


class VolumeData : protected QOpenGLExtraFunctions
{
public:
	explicit VolumeData();
	VolumeData(GLuint loc, const MainWindow* _mainWindow);
	void loadVolume(QString path);
	const void bind();
private:
	void uploadTexture(const char* data);
	const MainWindow* mainWindow;
	GLuint location = 0;
	QByteArray data = QByteArray();

};

