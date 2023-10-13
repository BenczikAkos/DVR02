#pragma once
#include <QByteArray>

class Array3D
{
private:
	int xSize;
	int ySize;
	int zSize;
	QByteArray bytes;
public:
	Array3D(int _xSize, int _ySize, int _zSize, QByteArray& _data);
	int xsize() const { return xSize; };
	int ysize() const { return ySize; };
	int zsize() const { return zSize; };
	QByteArray data() { return bytes; };
	int operator()(const int x, const int y, const int z);
	QVector<int> slice(const int x1, const int x2, const int y1, const int y2, const int z1, const int z2);
};

