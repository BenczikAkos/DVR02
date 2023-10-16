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

void BoundingGeometry::update()
{
	QSet<QPointF> pointCloud = {};
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
	// vertices = convexHull(pointCloud);
	// indices???
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

QSet<QPointF> BoundingGeometry::addCube(const int x, const int y, const int z)
{
	auto result = new QSet<QPointF>();
	int xMax = volume->xsize();
	int yMax = volume->ysize();
	int zMax = volume->zsize();
	float xSideLenght = blockSize / xMax;
	float ySideLenght = blockSize / yMax;
	float zSideLenght = blockSize / zMax;
}
