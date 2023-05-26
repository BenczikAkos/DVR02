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
    uploadTexture(data.data());
}

void VolumeData::uploadTexture(const char* data) {
    auto sizes = mainWindow->getDataSizes();
    glDeleteTextures(1, &location);
    glGenTextures(1, &location);
    glBindTexture(GL_TEXTURE_3D, location);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_R8, (int)sizes.x(), (int)sizes.y(), (int)sizes.z(), 0, GL_RED, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_3D, 0);
}

const void VolumeData::bind(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, location);
}