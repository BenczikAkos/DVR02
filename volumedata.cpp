#include "volumedata.h"
#include <QVector3D>
#include <qfile.h>

VolumeData::VolumeData()
{
    location = 0;
    mainWindow = nullptr;
    initializeOpenGLFunctions();
}

VolumeData::VolumeData(GLuint loc, const MainWindow* _mainWindow)
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
    createBarChart();
}

void VolumeData::uploadTexture() {
    auto sizes = mainWindow->getDataSizes(); int x = (int)sizes.x(); int y = (int)sizes.y(); int z = (int)sizes.z();
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

void VolumeData::createBarChart() const {

}

const void VolumeData::bind(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, location);
}