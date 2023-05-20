
#include "volumerenderwidget.h"
#include <QKeyEvent>
#include <qfile.h>


VolumeRenderWidget::VolumeRenderWidget(QWidget* parent)
    : QOpenGLWidget {parent}
{
    setFocusPolicy(Qt::StrongFocus);
    //setMouseTracking(true);
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

    GLuint VolumeLocation = m_program->uniformLocation("Volume");
    Q_ASSERT(VolumeLocation != -1);
    volume = new VolumeData(VolumeLocation);

}

void VolumeRenderWidget::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    m_program->setUniformValue(LocViewMatrix, viewMatrix);
    m_program->setUniformValue(LocCameraPos, CameraPos);
    volume->bind();
    //TODO: ne kérjük már el minden frame-ben, legyen tagváltozó
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
        QString path = QFileDialog::getOpenFileName(this, tr("Open volume"), "..\\datasets\\raw", tr("RAW images(*.raw);;DAT files(*.dat)"));
        if (!path.isNull()) {
            volume->loadVolume(path);
        }
    }
}

void VolumeRenderWidget::mousePressEvent(QMouseEvent *event)
{
    mouse_lastPos = event->pos();
    if(MouseFirstPressed){
        camera_lastPos = CameraPos;
        MouseFirstPressed = false;
    }
}

void VolumeRenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    MouseFirstPressed = true;
}

void VolumeRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - mouse_lastPos.x();
    int dy = event->y() - mouse_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot - dy);
        setYRotation(yRot + dx);
    }
    else if (event->buttons() & Qt::RightButton) {
        phi -= (float)dx / 20;
        elevation += (float)dy / 20;
        rotateScene(phi, elevation);
    }
    viewMatrix.setToIdentity();
    viewMatrix.rotate(xRot, 1, 0, 0);
    viewMatrix.rotate(yRot, 0, 1, 0);
    viewMatrix.rotate(zRot, 0, 0, 1);
    mouse_lastPos = event->pos();
}

void VolumeRenderWidget::wheelEvent(QWheelEvent* event) {
    CameraPos += event->angleDelta().y() * QVector3D(0.0f, 0.0f, 0.01f) * viewMatrix;
}

void VolumeRenderWidget::rotateScene(float phi, float theta){
    qWarning() << CameraPos << " phi: " << phi << " theta: " << theta;
    QVector3D origo = QVector3D(0.0f, 0.0f, 0.0f);
    float radius = CameraPos.distanceToPoint(origo);

    CameraPos.setX(radius * cos(phi) * cos(theta));
    CameraPos.setY(radius * sin(theta));
    CameraPos.setZ(radius * sin(phi) * cos(theta));
    setXRotation(fromRadian(M_PI - theta));
    setYRotation(fromRadian(M_PI / 2 - phi));
}

float VolumeRenderWidget::fromRadian(float angle) {
    return angle * 180 / M_PI;
}

void VolumeRenderWidget::normalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;
}

void VolumeRenderWidget::setXRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
    }
}

void VolumeRenderWidget::setYRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
    }
}

void VolumeRenderWidget::setZRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
    }
}
