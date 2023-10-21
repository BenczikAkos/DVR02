#pragma once
#include <QObject>
#include "volumedata.h"
#include "visualizationsetting.h"

class BoundingGeometry: public QObject
{
    Q_OBJECT
public:
    BoundingGeometry() = default;
    BoundingGeometry(std::shared_ptr<VolumeData> _data, std::shared_ptr<VisualizationSetting> _visualization);
    const GLfloat* getVertices() const;
    const GLuint* getIndices() const;
    const GLsizei getIndexCount() const;
public slots:
    void update();
    void setBlockSize(int _blockSize);
private:
    QVector<GLfloat> vertices = {
        0.0f, 0.0f, 0.0f, // 0
        1.0f, 0.0f, 0.0f, // 1
        1.0f, 1.0f, 0.0f, // 2
        0.0f, 1.0f, 0.0f, // 3
        0.0f, 0.0f, 1.0f, // 4
        1.0f, 0.0f, 1.0f, // 5
        1.0f, 1.0f, 1.0f, // 6
        0.0f, 1.0f, 1.0f  // 7
    };
    QVector<GLuint> indices = {
        0, 1, 2,  // Front
        2, 3, 0,
        1, 5, 6,  // Right
        6, 2, 1,
        7, 6, 5,  // Top
        5, 4, 7,
        4, 0, 3,  // Left
        3, 7, 4,
        4, 5, 1,  // Bottom
        1, 0, 4,
        3, 2, 6,  // Back
        6, 7, 3
    };
    QVector<GLuint> indicesTemplate = {
    0, 1, 2,  // Front
    2, 3, 0,
    1, 5, 6,  // Right
    6, 2, 1,
    7, 6, 5,  // Top
    5, 4, 7,
    4, 0, 3,  // Left
    3, 7, 4,
    4, 5, 1,  // Bottom
    1, 0, 4,
    3, 2, 6,  // Back
    6, 7, 3
    };
    uint blockSize = 8;
    std::shared_ptr<VolumeData> volume;
    std::shared_ptr<VisualizationSetting> visualizationSetting;
    bool isContributing(QVector<int> voxelValues);
    void addTriangle(const QVector3D& p1, const QVector3D& p2, const QVector3D& p3, QList<QVector3D>& _vertexList, QList<QVector3D>& _indexList);
    QSet<QVector3D> addCube(const int x, const int y, const int z);
    void generateConvexHull(QSet<QVector3D> _pointCloud);
};