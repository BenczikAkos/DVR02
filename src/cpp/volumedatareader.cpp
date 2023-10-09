#include "../include/volumedatareader.h"

VolumeDataReader::VolumeDataReader() = default;

//Setters
void VolumeDataReader::setDataType(int type)
{
    switch (type) {
    case 0:
        dataType = GL_UNSIGNED_BYTE;
        break;
    case 1:
        dataType = GL_UNSIGNED_SHORT;
        break;
    case 2:
        dataType = GL_UNSIGNED_INT;
        break;
    case 3:
        dataType = GL_BYTE;
        break;
    case 4:
        dataType = GL_SHORT;
        break;
    case 5:
        dataType = GL_INT;
        break;
    case 6:
        dataType = GL_FLOAT;
        break;
    default:
        qWarning() << "Datatype index is out of range";
    }
}

void VolumeDataReader::setPrecomputeGradients(int _precomputeGradients)
{
    precomputeGradients = _precomputeGradients == 2; //0: unchecked, 1: partially checked, 2: checked based on QtCheckState
}

void VolumeDataReader::setLittleEndian(int _isLittleEndian)
{
    isLittleEndian = _isLittleEndian == 2;
}

void VolumeDataReader::setXTextureSize(int newValue) {
    xTextureSize = newValue;
}

void VolumeDataReader::setYTextureSize(int newValue) {
    yTextureSize = newValue;
}

void VolumeDataReader::setZTextureSize(int newValue) {
    zTextureSize = newValue;
}

//Getters
void VolumeDataReader::getTextureSizes(int& x, int& y, int& z) {
    x = xTextureSize;
    y = yTextureSize;
    z = zTextureSize;
}

bool VolumeDataReader::getPrecomputeGradients() {
    return precomputeGradients;
}

GLenum VolumeDataReader::getDataType()
{
    return dataType;
}

bool VolumeDataReader::getLittleEndian()
{
    return isLittleEndian;
}
