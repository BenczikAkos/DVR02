#pragma once
#include "QtOpenGLWidgets/qopenglwidget.h"
#include "mainwindow.h"
#include <qopenglextrafunctions.h>
#include <qopenglfunctions_4_5_core.h>

class VolumeData : protected QOpenGLFunctions_4_5_Core
{
private:
	int xSize = 128;
	int ySize = 128;
	int zSize = 128;
	QByteArray data = QByteArray();
public:
	explicit VolumeData();
	VolumeData(GLuint loc, VolumeDataReader* _reader);
	void loadVolume(QString path);
	QChart* createChart() const;
	void bind();
	int xsize() const { return xSize; };
	int ysize() const { return ySize; };
	int zsize() const { return zSize; };
	int operator()(const int x, const int y, const int z);
	QVector<int> slice(const int x1, const int x2, const int y1, const int y2, const int z1, const int z2);
private:
	void uploadTexture();
	char computeGrad(const int position, const QByteArray& values, const int stepsize);
	VolumeDataReader* reader;
	GLuint location = 0;

};

