
#include "volumerenderwindow.h"
#include <QKeyEvent>
#include <qfile.h>

void VolumeRenderWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    LocViewMatrix = m_program->uniformLocation("ViewMatrix");
    Q_ASSERT(LocViewMatrix != -1);
    LocCameraPos = m_program->uniformLocation("CameraPos");
    Q_ASSERT(LocCameraPos != -1);
    LocWindowSize = m_program->uniformLocation("WindowSize");
    Q_ASSERT(LocWindowSize != -1);
}

void VolumeRenderWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    m_program->setUniformValue(LocViewMatrix, viewMatrix);
    m_program->setUniformValue(LocCameraPos, CameraPos);

    QVector2D windowSize = QVector2D(this->width(), this->height());
    m_program->setUniformValue(LocWindowSize, windowSize);

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(m_posAttr);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();
}

void VolumeRenderWindow::keyPressEvent(QKeyEvent *ev)
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
        loadVolume("D:\\Egyetem\\6semester\\Onlab\\datasets\\raw\\skull-256x256x256\\skull.raw");
    }
}

void VolumeRenderWindow::mousePressEvent(QMouseEvent *event)
{
    mouse_lastPos = event->pos();
    if(MouseFirstPressed){
        camera_lastPos = CameraPos;
        //qWarning() << camera_lastPos;
        MouseFirstPressed = false;
    }
}

void VolumeRenderWindow::mouseReleaseEvent(QMouseEvent *event)
{
    MouseFirstPressed = true;
}

void VolumeRenderWindow::loadVolume(QString path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Not successful";
        return;
    };
    QByteArray blob = file.readAll();
    for (int i = 0; i < 25; i++) {
        qWarning() << (int)(blob.at(i));
    }
    qWarning() << "Blobsize: " << blob.size();
}

void VolumeRenderWindow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - mouse_lastPos.x();
    int dy = event->y() - mouse_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton) {
        aroundAngle += dx;
        qWarning() << aroundAngle;
        rotateScene(-aroundAngle/10);
    }
    viewMatrix.setToIdentity();
    viewMatrix.rotate(180.0f - (xRot / 16.0f), 1, 0, 0);
    viewMatrix.rotate(yRot / 16.0f, 0, 1, 0);
    viewMatrix.rotate(zRot / 16.0f, 0, 0, 1);
    mouse_lastPos = event->pos();
}

void VolumeRenderWindow::rotateScene(float angle){
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

void VolumeRenderWindow::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
    }
}

void VolumeRenderWindow::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
    }
}

void VolumeRenderWindow::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
    }
}
