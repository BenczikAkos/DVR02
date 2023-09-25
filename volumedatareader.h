#pragma once
#include <qopenglextrafunctions.h>

enum class Mode {
	MIP = 0,
	Accumulate = 1,
	Average = 2,
	Isosurface = 3
};

class VolumeDataReader : public QObject
{
	Q_OBJECT

public:
	explicit VolumeDataReader();
	void getTextureSizes(int& x, int& y, int& z);
	bool getPrecomputeGradients();
	GLenum getDataType();
public slots:
	void setXTextureSize(int newvalue);
	void setYTextureSize(int newvalue);
	void setZTextureSize(int newvalue);
	void setDataType(int type);
	void setPrecomputeGradients(int _precomputeGradients);
	void setLittleEndian(bool _isLittleEndian);
private:
	int xTextureSize = 256;
	int yTextureSize = 256;
	int zTextureSize = 256;
	GLenum dataType = GL_UNSIGNED_BYTE;
	bool precomputeGradients = false;
	bool isLittleEndian = false;
};

