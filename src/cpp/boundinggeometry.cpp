#include "../include/boundinggeometry.h"

BoundingGeometry::BoundingGeometry(std::shared_ptr<VolumeData> _data, std::shared_ptr<VisualizationSetting> _visualization)
	: volume(_data),
	visualizationSetting(_visualization)
{
}

const float* BoundingGeometry::getVertices() const
{
	return vertices.constData();
}

const uint* BoundingGeometry::getIndices() const
{
	return indices.constData();
}

const GLsizei BoundingGeometry::getIndexCount() const
{
	return GLsizei(indices.size());
}

uint qHash(const QVector3D& v)
{
	return qHash(QString("%1x%2x%3").arg(v.x()).arg(v.y()).arg(v.z()));
}

void BoundingGeometry::update()
{
	QSet<QVector3D> pointCloud;
	vertices.clear();
	indices.clear();
	int xMax = volume->xsize();
	int yMax = volume->ysize();
	int zMax = volume->zsize();
	for (int x = 0; x < xMax; x += blockSize)
	{
		for (int y = 0; y < yMax; y += blockSize)
		{
			for (int z = 0; z < zMax; z += blockSize)
			{
				auto regionOfInterest = volume->slice(x, x + blockSize, y, y + blockSize, z, z + blockSize);
				if (isContributing(regionOfInterest))
				{
					pointCloud |= addCube(x, y, z);
				}
			}
		}
	}
	generateConvexHull(pointCloud, vertices, indices);
}

void BoundingGeometry::setBlockSize(int _blockSize)
{
	if (_blockSize < 1)
	{
		_blockSize = 1;
	}
	blockSize = _blockSize;
}

bool BoundingGeometry::isContributing(QVector<int> voxels)
{
	bool isContributing = false;
	for (auto voxel : voxels)
	{
		if (!visualizationSetting->isTransparent(voxel))
		{
			isContributing = true;
			break;
		}
	}
	return isContributing;
}

QSet<QVector3D> BoundingGeometry::addCube(const int x, const int y, const int z)
{
	auto result = QSet<QVector3D>();
	int xMax = volume->xsize();
	int yMax = volume->ysize();
	int zMax = volume->zsize();
	float xSideLenght = blockSize / xMax; auto xSideVector = QVector3D(xSideLenght, 0, 0);
	float ySideLenght = blockSize / yMax; auto ySideVector = QVector3D(0, ySideLenght, 0);
	float zSideLenght = blockSize / zMax; auto zSideVector = QVector3D(0, 0, zSideLenght);
	auto left_bottom_back_corner = QVector3D((float)x / xMax, (float)y / yMax, (float)z / zMax);

	result.insert(left_bottom_back_corner);
	result.insert(left_bottom_back_corner + xSideVector);
	result.insert(left_bottom_back_corner + ySideVector);
	result.insert(left_bottom_back_corner + zSideVector);
	result.insert(left_bottom_back_corner + xSideVector + ySideVector);
	result.insert(left_bottom_back_corner + xSideVector + zSideVector);
	result.insert(left_bottom_back_corner + ySideVector + zSideVector);
	result.insert(left_bottom_back_corner + xSideVector + ySideVector + zSideVector);
	return result;
}

void BoundingGeometry::generateConvexHull(QSet<QVector3D> _pointCloud, QVector<float>& _vertices, QVector<uint>& indices)
{
}
