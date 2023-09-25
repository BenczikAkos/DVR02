#include "volumedata.h"
#include <QVector3D>
#include <QChart>
#include <qfile.h>
#include <QLineSeries>

VolumeData::VolumeData()
{
    location = 0;
    mainWindow = nullptr;
    initializeOpenGLFunctions();
}

VolumeData::VolumeData(GLuint loc, MainWindow* _mainWindow)
    : location { loc },
    mainWindow { _mainWindow }
{
    initializeOpenGLFunctions();
}

void VolumeData::loadVolume(QString path, boolean precompute_grads, GLenum dataType) {
    data = nullptr;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "File opening not successful";
        return;
    };
    QByteArray values = file.readAll();
    file.close();
    auto sizes = mainWindow->getDataSizes(); int x = (int)sizes.x(); int y = (int)sizes.y();
    for (int i = 0; i < values.size(); ++i) {
        data.append(values.at(i));
        if (precompute_grads)
        {
            char grad_x = computeGrad(i, values, 1);
            char grad_y = computeGrad(i, values, x);
            char grad_z = computeGrad(i, values, x * y);
            data.append(grad_x);
            data.append(grad_y);
            data.append(grad_z);
        }
    }

    qWarning() << "Nb of datapoints: " << data.size();
    uploadTexture(precompute_grads, dataType);
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

void VolumeData::uploadTexture(boolean precompute_grads, GLenum dataType) {
    auto sizes = mainWindow->getDataSizes(); int x = (int)sizes.x(); int y = (int)sizes.y(); int z = (int)sizes.z();
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
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_LSB_FIRST, 1);
    if (precompute_grads) {
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, x, y, z, 0, GL_RGBA, dataType, data.data());
    }
    else {
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, x, y, z, 0, GL_RED, dataType, data.data());
    }
    glBindTexture(GL_TEXTURE_3D, 0);
}


const void VolumeData::bind(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, location);
}