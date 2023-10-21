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
	int interestingCubes = 0;
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
					interestingCubes++;
				}
			}
		}
	}
	qWarning() << "Interesting cubes: " << interestingCubes;
	//generateConvexHull(pointCloud);
}

void BoundingGeometry::setBlockSize(int _blockSize)
{
	if (_blockSize < 1)
	{
		_blockSize = 1;
	}
	blockSize = _blockSize;
}

bool BoundingGeometry::isContributing(QVector<int> voxelValues)
{
	bool isContributing = false;
	for (auto voxel : voxelValues)
	{
		if (!visualizationSetting->isTransparent(voxel))
		{
			isContributing = true;
			break;
		}
	}
	return isContributing;
}

void BoundingGeometry::addTriangle(const QVector3D& p1, const QVector3D& p2, const QVector3D& p3, QList<QVector3D>& _vertexList, QList<QVector3D>& _indexList)
{
	int i1 = _vertexList.indexOf(p1);
	if (i1 == -1)
	{
		i1 = _vertexList.size();
		_vertexList.append(p1);
	}
	int i2 = _vertexList.indexOf(p2);
	if (i2 == -1)
	{
		i2 = _vertexList.size();
		_vertexList.append(p2);
	}
	int i3 = _vertexList.indexOf(p3);
	if (i3 == -1)
	{
		i3 = _vertexList.size();
		_vertexList.append(p3);
	}
	_indexList.append(QVector3D(i1, i2, i3));
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
	
	vertices.append(left_bottom_back_corner.x());
	vertices.append(left_bottom_back_corner.y());
	vertices.append(left_bottom_back_corner.z());
	vertices.append((left_bottom_back_corner + xSideVector).x());
	vertices.append((left_bottom_back_corner + xSideVector).y());
	vertices.append((left_bottom_back_corner + xSideVector).z());
	vertices.append((left_bottom_back_corner + xSideVector + ySideVector).x());
	vertices.append((left_bottom_back_corner + xSideVector + ySideVector).y());
	vertices.append((left_bottom_back_corner + xSideVector + ySideVector).z());
	vertices.append((left_bottom_back_corner + ySideVector).x());
	vertices.append((left_bottom_back_corner + ySideVector).y());
	vertices.append((left_bottom_back_corner + ySideVector).z());
	vertices.append((left_bottom_back_corner + zSideVector).x());
	vertices.append((left_bottom_back_corner + zSideVector).y());
	vertices.append((left_bottom_back_corner + zSideVector).z());
	vertices.append((left_bottom_back_corner + xSideVector + zSideVector).x());
	vertices.append((left_bottom_back_corner + xSideVector + zSideVector).y());
	vertices.append((left_bottom_back_corner + xSideVector + zSideVector).z());
	vertices.append((left_bottom_back_corner + xSideVector + ySideVector + zSideVector).x());
	vertices.append((left_bottom_back_corner + xSideVector + ySideVector + zSideVector).y());
	vertices.append((left_bottom_back_corner + xSideVector + ySideVector + zSideVector).z());
	vertices.append((left_bottom_back_corner + ySideVector + zSideVector).x());
	vertices.append((left_bottom_back_corner + ySideVector + zSideVector).y());
	vertices.append((left_bottom_back_corner + ySideVector + zSideVector).z());

	uint offset = vertices.size() / 3 - 8;
	for (auto index : indicesTemplate)
	{
		indices.append(index + offset);
	}
	return result;
}

void BoundingGeometry::generateConvexHull(QSet<QVector3D> _pointCloud)
{
	QList<QVector3D> vertexList;
	QList<QVector3D> indexList;
	// from pointcloud return the biggest tethahedron based on this pseudo code:
	  // For each principle direction (X-axis, Y-axis, Z-axis) find the minimum and maximum point in that dimension
	  // The two points with the greatest distance between them are the first two points of the tetrahedron
	  // The third point is the point with the greatest distance from the line between the first two points
	  // The fourth point is the point with the greatest distance from the plane defined by the first three points
	  // The tetrahedron is now defined by the four points
	QVector3D xMin = QVector3D(1.0f, 0.0f, 0.0f);
	QVector3D xMax = QVector3D(0.0f, 0.0f, 0.0f);
	QVector3D yMin = QVector3D(0.0f, 1.0f, 0.0f);
	QVector3D yMax = QVector3D(0.0f, 0.0f, 0.0f);
	QVector3D zMin = QVector3D(0.0f, 0.0f, 1.0f);
	QVector3D zMax = QVector3D(0.0f, 0.0f, 0.0f);
	//search for the min and max values in each dimension
	for (auto point : _pointCloud)
	{
		if (point.x() < xMin.x())
		{
			xMin = point;
		}
		if (point.x() > xMax.x())
		{
			xMax = point;
		}
		if (point.y() < yMin.y())
		{
			yMin = point;
		}
		if (point.y() > yMax.y())
		{
			yMax = point;
		}
		if (point.z() < zMin.z())
		{
			zMin = point;
		}
		if (point.z() > zMax.z())
		{
			zMax = point;
		}
	}
	float xDistance = xMax.distanceToPoint(xMin);
	float yDistance = yMax.distanceToPoint(yMin);
	float zDistance = zMax.distanceToPoint(zMin);
	//selecting the two points with the greatest distance between them
	QVector3D p1 = xMin;
	QVector3D p2 = xMax;
	if (yDistance > xDistance && yDistance > zDistance)
	{
		p1 = yMin;
		p2 = yMax;
	}
	else if (zDistance > xDistance && zDistance >= yDistance)
	{
		p1 = zMin;
		p2 = zMax;
	}
	//selecting the third point which is the point with the greatest distance from the line between the first two points
	QVector3D p3 = QVector3D(0.0f, 0.0f, 0.0f);
	float maxDistance = 0.0f;
	QVector3D lineDirection = (p2 - p1).normalized();
	qWarning() << _pointCloud.size();
	for (auto point : _pointCloud)
	{
		float distance = point.distanceToLine(p1, lineDirection);
		if (distance > maxDistance)
		{
			maxDistance = distance;
			p3 = point;
		}
	}
	//selecting the fourth point which is the point with the greatest distance from the plane defined by the first three points
	QVector3D p4 = QVector3D(0.0f, 0.0f, 0.0f);
	maxDistance = 0.0f;
	for (auto point : _pointCloud)
	{
		float distance = point.distanceToPlane(p1, p2, p3);
		if (distance > maxDistance || -distance > maxDistance)
		{
			maxDistance = distance;
			p4 = point;
		}
	}
	if (maxDistance < 0.0f) // if the fourth point is on the other side of the plane, we have to swap the third and the first point
	{
		auto tmp = p3;
		p3 = p1;
		p1 = tmp;
	}
	addTriangle(p1, p2, p3, vertexList, indexList);
	addTriangle(p1, p2, p4, vertexList, indexList);
	addTriangle(p2, p3, p4, vertexList, indexList);
	addTriangle(p3, p1, p4, vertexList, indexList);
	vertices.clear();
	indices.clear();
	for (auto vertex : vertexList)
	{
		vertices.append((GLfloat)vertex.x());
		vertices.append((GLfloat)vertex.y());
		vertices.append((GLfloat)vertex.z());
	}
	for (auto index : indexList)
	{
		indices.append((GLuint)index.x());
		indices.append((GLuint)index.y());
		indices.append((GLuint)index.z());
	}
}
