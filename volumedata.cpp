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
    qWarning() << _mainWindow;
    initializeOpenGLFunctions();
}

void VolumeData::loadVolume(QString path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Not successful";
        return;
    };
    data = file.readAll();
    qWarning() << "Nb of datapoints: " << data.size();
    uploadTexture();
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
    auto sizes = mainWindow->getDataSizes(); int x = (int)sizes.x(); int y = (int)sizes.y(); int z = (int)sizes.z();
    if(x*y*z != data.size())
    {
        qWarning() << "Wrong texture sizes!";
        return;
    }
    glDeleteTextures(1, &location);
    glGenTextures(1, &location);
    glBindTexture(GL_TEXTURE_3D, location);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_R8, x, y, z, 0, GL_RED, GL_UNSIGNED_BYTE, data.data());
    glBindTexture(GL_TEXTURE_3D, 0);
}


const void VolumeData::bind(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, location);
}