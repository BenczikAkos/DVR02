#include "../include/volumedata.h"
#include <QVector3D>
#include <QChart>
#include <qfile.h>
#include <QLineSeries>

VolumeData::VolumeData()
{
    location = 0;
    reader = nullptr;
    initializeOpenGLFunctions();
}

VolumeData::VolumeData(GLuint loc, VolumeDataReader* _reader)
    : location { loc },
    reader { _reader }
{
    initializeOpenGLFunctions();
}

void VolumeData::loadVolume(QString path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "File opening not successful";
        return;
    };
    reader->getTextureSizes(xSize, ySize, zSize);
    if (reader->getPrecomputeGradients())
    {
        QByteArray values = file.readAll();
        for (int i = 0; i < values.size(); ++i)
        {
            data.append(values.at(i));
            char grad_x = computeGrad(i, values, 1);
            char grad_y = computeGrad(i, values, xSize);
            char grad_z = computeGrad(i, values, xSize * ySize);
            data.append(grad_x);
            data.append(grad_y);
            data.append(grad_z);
        }
    }
    else
    {
        data = file.readAll();
    }

    file.close();
    qWarning() << "Nb of datapoints: " << data.size();
    uploadTexture();
}

int VolumeData::operator()(const int x, const int y, const int z)
{
    if (x >= xSize || x < 0 ||
        y >= ySize || y < 0 ||
        z >= zSize || z < 0)
    {
        return 0.0f;
    }
    int idx = z * xSize * ySize + y * xSize + x;
    return (int)data.at(idx);
}

QVector<int> VolumeData::slice(const int x1, const int x2, const int y1, const int y2, const int z1, const int z2)
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

char VolumeData::computeGrad(const int position, const QByteArray& values, const int stepsize) {
    char minus1, plus1;
    if (stepsize > position) {
        minus1 = values.at(position);
        plus1 = values.at(position + stepsize);
    }
    else if (position + stepsize >= values.size()) {
        minus1 = values.at(position - stepsize);
        plus1 = values.at(position);
    }
    else {
        minus1 = values.at(position - stepsize);
        plus1 = values.at(position + stepsize);
    }
    return (plus1 - minus1) / (char)2;
}

QChart* VolumeData::createChart() const {
    QMap<unsigned char, qreal> valueCounts;
    for (auto byte : data) {
        if (byte != 0)
        {
            if (valueCounts.contains(byte)) {
                valueCounts[byte] += 1.0;
            }
            else {
                valueCounts[byte] = 1.0;
            }
        }
    }

    QLineSeries* series = new QLineSeries();
    for (int i = 0; i < valueCounts.values().size(); ++i) {
        series->append(i, valueCounts.values()[i]);
    }
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->hide();
    return chart;
}

void VolumeData::uploadTexture() {
    reader->getTextureSizes(xSize, ySize, zSize);
    GLenum dataType = reader->getDataType();
    //if( (precompute_grads && x*y*z*4 != data.size()) || (!precompute_grads && x*y*z != data.size()) )
    //{
    //    int coef = precompute_grads ? 4 : 1;
    //    qWarning() << "Wrong texture sizes!" << x*y*z*coef << " vs. " << data.size();
    //    return;
    //}
    glDeleteTextures(1, &location);
    glGenTextures(1, &location);
    glBindTexture(GL_TEXTURE_3D, location);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //tightly packed
    if (reader->getLittleEndian()) {
        glPixelStorei(GL_UNPACK_LSB_FIRST, 1);
    }
    else {
        glPixelStorei(GL_UNPACK_LSB_FIRST, 0);
    }
    if (reader->getPrecomputeGradients()) {
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, xSize, ySize, zSize, 0, GL_RGBA, dataType, data.data());
    }
    else {
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, xSize, ySize, zSize, 0, GL_RED, dataType, data.data());
    }
    int width, height, depth, internalFormat = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_DEPTH, &depth);
    glGetTexLevelParameteriv(GL_TEXTURE_3D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &internalFormat);
    qDebug() << "Texture size: " << width << "x" << height << "x" << depth << " internal format: " << internalFormat;
    glBindTexture(GL_TEXTURE_3D, 0);
}


void VolumeData::bind() 
{
    glActiveTexture(GL_TEXTURE0 + location);
    glBindTexture(GL_TEXTURE_3D, location);
}