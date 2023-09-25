#pragma once
#include "QtOpenGLWidgets/qopenglwidget.h"
#include "mainwindow.h"
#include <qopenglextrafunctions.h>


class VolumeData : protected QOpenGLExtraFunctions
{
public:
	explicit VolumeData();
	VolumeData(GLuint loc, VolumeDataReader* _reader);
	void loadVolume(QString path);
	QChart* createChart() const;
	const void bind();
private:
	void uploadTexture();
	char computeGrad(const int position, const QByteArray& values, const int stepsize);
	VolumeDataReader* reader;
	GLuint location = 0;
	QByteArray data = QByteArray();

};

