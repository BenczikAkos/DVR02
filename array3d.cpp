#include "array3d.h"
#include <QVector>

Array3D::Array3D(int _xSize, int _ySize, int _zSize, QByteArray& _data) :
	xSize(_xSize),
	ySize(_ySize),
	zSize(_zSize),
	bytes(_data)
{}

int Array3D::operator()(const int x, const int y, const int z)
{
	if (x >= xSize || x < 0 ||
		y >= ySize || y < 0 ||
		z >= zSize || z < 0)
	{
		return 0.0f;
	}
	int idx = z * xSize * ySize + y * xSize + x;
	return (int)bytes.at(idx);
}

QVector<int> Array3D::slice(const int x1, const int x2, const int y1, const int y2, const int z1, const int z2)
{
	auto result = QVector<int>();
	Q_ASSERT(x1 < x2);
	Q_ASSERT(y1 < y2);
	Q_ASSERT(z1 < z2);
	for (int x = x1; x < x2; ++x)
	{
		for (int y = y1; y < y2; ++y)
		{
			for (int z = z1; z < z2; ++z)
			{
				result.append(this->operator()(x, y, z));
			}
		}
	}
	return result;
}
