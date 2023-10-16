#pragma once
#include <QObject>

class BoundingGeometry: public QObject
{
    Q_OBJECT
public:
    BoundingGeometry() = default;
    const float* getVertices();
    const uint* getIndices();
private:
    QVector<float> vertices = {
        0.0f, 0.0f, 0.0f, // 0
        1.0f, 0.0f, 0.0f, // 1
        1.0f, 1.0f, 0.0f, // 2
        0.0f, 1.0f, 0.0f, // 3
        0.0f, 0.0f, 1.0f, // 4
        1.0f, 0.0f, 1.0f, // 5
        1.0f, 1.0f, 1.0f, // 6
        0.0f, 1.0f, 1.0f  // 7
    };
    QVector<uint> indices = {
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
};