#pragma once
#include "QtOpenGLWidgets/qopenglwidget.h"
#include <qopenglextrafunctions.h>


class VolumeData : protected QOpenGLExtraFunctions
{
public:
	explicit VolumeData();
	VolumeData(GLuint loc);
	void loadVolume(QString path);
	const void bind();
private:
	void uploadTexture(const char* data);
	GLuint location = 0;
	QByteArray data = QByteArray();

};

