
#include "volumerenderwidget.h"
#include <QKeyEvent>
#include <qfile.h>


VolumeRenderWidget::VolumeRenderWidget(QWidget* parent)
    : QOpenGLWidget {parent}
{
    setFocusPolicy(Qt::StrongFocus);
    update();
}

VolumeRenderWidget::~VolumeRenderWidget()
{

}

void VolumeRenderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    if(!m_program->link()){
        qWarning() << m_program->log();
    }
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    LocViewMatrix = m_program->uniformLocation("ViewMatrix");
    Q_ASSERT(LocViewMatrix != -1);
    LocCameraPos = m_program->uniformLocation("CameraPos");
    Q_ASSERT(LocCameraPos != -1);
    LocWindowSize = m_program->uniformLocation("WindowSize");
    Q_ASSERT(LocWindowSize != -1);
    LocVolumeSampler = m_program->uniformLocation("Volume");
    Q_ASSERT(LocVolumeSampler != -1);

}

void VolumeRenderWidget::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    m_program->setUniformValue(LocViewMatrix, viewMatrix);
    m_program->setUniformValue(LocCameraPos, CameraPos);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, LocVolumeSampler);

    QVector2D windowSize = QVector2D(this->width(), this->height());
    m_program->setUniformValue(LocWindowSize, windowSize);

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(m_posAttr);
    glBindVertexArray(m_posAttr);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();
    update();
}

void VolumeRenderWidget::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
    case Qt::Key_W:
        CameraPos += QVector3D(0.0f, 0.0f, 0.03f) * viewMatrix; break;
    case Qt::Key_S:
        CameraPos += QVector3D(0.0f, 0.0f, -0.03f) * viewMatrix; break;
    case Qt::Key_A:
        CameraPos += QVector3D(-0.03f, 0.0f, 0.0f) * viewMatrix; break;
    case Qt::Key_D:
        CameraPos += QVector3D(0.03f, 0.0f, 0.0f) * viewMatrix; break;
    case Qt::Key_Q:
        CameraPos += QVector3D(0.0f, 0.03f, 0.0f); break;
    case Qt::Key_E:
        CameraPos += QVector3D(0.0f, -0.03f, 0.0f); break;
    case Qt::Key_O:
        loadVolume("D:\\Egyetem\\6semester\\Onlab\\datasets\\raw\\foot.raw");
    }
}

void VolumeRenderWidget::mousePressEvent(QMouseEvent *event)
{
    mouse_lastPos = event->pos();
    if(MouseFirstPressed){
        camera_lastPos = CameraPos;
        qWarning() << camera_lastPos;
        MouseFirstPressed = false;
    }
}

void VolumeRenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    MouseFirstPressed = true;
}

void VolumeRenderWidget::loadVolume(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Not successful";
        return;
    };
    VolumeData = file.readAll();
    unsigned char max = 0;
    for (int i = 0; i < VolumeData.size(); ++i) {
        if ((unsigned char)VolumeData.at(i) > max) {
            max = (unsigned char)VolumeData.at(i);
        }
    }
    qWarning() << "Blobsize: " << VolumeData.size() << " max value: " << max;
    generateTexture(VolumeData.data());
}

void VolumeRenderWidget::generateTexture(const char* data) {
    glDeleteTextures(1, &LocVolumeSampler);
    glGenTextures(1, &LocVolumeSampler);
    glBindTexture(GL_TEXTURE_3D, LocVolumeSampler);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_R8, 256, 256, 256, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_3D, 0);
}

void VolumeRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - mouse_lastPos.x();
    int dy = event->y() - mouse_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton) {
        aroundAngle += dx;
        rotateScene(-aroundAngle/10);
    }
    viewMatrix.setToIdentity();
    viewMatrix.rotate(180.0f - (xRot / 16.0f), 1, 0, 0);
    viewMatrix.rotate(yRot / 16.0f, 0, 1, 0);
    viewMatrix.rotate(zRot / 16.0f, 0, 0, 1);
    mouse_lastPos = event->pos();
}

void VolumeRenderWidget::rotateScene(float angle){
    QVector3D origo = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D upY = QVector3D(0.0f, 1.0f, 0.0f);
    float radius = CameraPos.distanceToLine(origo, upY);
    //angle += aroundAngle;

    CameraPos.setX(radius * cos(angle));
    CameraPos.setZ(radius * sin(angle));
    setYRotation((M_PI/2 - angle)*180*16/M_PI);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void VolumeRenderWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
    }
}

void VolumeRenderWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
    }
}

void VolumeRenderWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
    }
}
