#include "../include/boundinggeometry.h"

const float* BoundingGeometry::getVertices()
{
	return vertices.constData();
}

const uint* BoundingGeometry::getIndices()
{
	return indices.constData();
}
