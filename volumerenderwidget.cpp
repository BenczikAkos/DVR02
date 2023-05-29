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

    GLuint VolumeLocation = m_program->uniformLocation("Volume");
    Q_ASSERT(VolumeLocation != -1);
    volume = new VolumeData(VolumeLocation, (MainWindow*)parentWidget()->parentWidget());

}

void VolumeRenderWidget::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    m_program->setUniformValue("ViewMatrix", ViewMatrix);
    m_program->setUniformValue("CameraPos", CameraPos);
    m_program->setUniformValue("AABBScale", AABBScale);
    volume->bind();
    //TODO: ne kerjuk már el minden frame-ben, legyen tagvaltozo
    QVector2D windowSize = QVector2D(this->width(), this->height());
    m_program->setUniformValue("WindowSize", windowSize);
    m_program->setUniformValue("intensityCap", intensityCap);

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
        CameraPos += QVector3D(0.0f, 0.0f, 0.03f) * ViewMatrix; break;
    case Qt::Key_S:
        CameraPos += QVector3D(0.0f, 0.0f, -0.03f) * ViewMatrix; break;
    case Qt::Key_A:
        CameraPos += QVector3D(-0.03f, 0.0f, 0.0f) * ViewMatrix; break;
    case Qt::Key_D:
        CameraPos += QVector3D(0.03f, 0.0f, 0.0f) * ViewMatrix; break;
    case Qt::Key_Q:
        CameraPos += QVector3D(0.0f, 0.03f, 0.0f); break;
    case Qt::Key_E:
        CameraPos += QVector3D(0.0f, -0.03f, 0.0f); break;
    case Qt::Key_O:
        openFile();
    }
}

void VolumeRenderWidget::openFile() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open volume"), "..\\datasets\\raw", tr("RAW images(*.raw);;DAT files(*.dat)"));
    if (!path.isNull()) {
        volume->loadVolume(path);
    }
}

QChart* VolumeRenderWidget::generateChart() const
{
    return volume->createChart();
}

void VolumeRenderWidget::mousePressEvent(QMouseEvent *event)
{
    mouse_lastPos = event->pos();
    if(MouseFirstPressed){
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
        setRotation(xRot - dy, xRot);
        //setRotation(zRot - dy, zRot);
        setRotation(yRot + dx, yRot);
    }
    else if (event->buttons() & Qt::RightButton) {
        phi -= (float)dx / 40;
        elevation += (float)dy / 40;
        rotateScene(phi, elevation);
    }
    ViewMatrix.setToIdentity();
    ViewMatrix.rotate(xRot, 1, 0, 0);
    ViewMatrix.rotate(yRot, 0, 1, 0);
    ViewMatrix.rotate(zRot, 0, 0, 1);
    mouse_lastPos = event->pos();
}

void VolumeRenderWidget::wheelEvent(QWheelEvent* event) {
    CameraPos += event->angleDelta().y() * QVector3D(0.0f, 0.0f, 0.0033f) * ViewMatrix;
}

void VolumeRenderWidget::rotateScene(float phi, float theta){
    QVector3D origo = QVector3D(0.0f, 0.0f, 0.0f);
    float radius = CameraPos.distanceToPoint(origo);

    CameraPos.setX(radius * cos(phi) * cos(theta));
    CameraPos.setY(radius * sin(theta));
    CameraPos.setZ(radius * sin(phi) * cos(theta));
    setRotation(fromRadian(M_PI - theta), xRot);
    setRotation(fromRadian(M_PI / 2 - phi), yRot);
}

void VolumeRenderWidget::setAABBScaleX(int value)
{
    qWarning() << value;
    AABBScale.setX(value / 300.0);
}

void VolumeRenderWidget::setAABBScaleY(int value)
{
    AABBScale.setY(value / 300.0);
}

void VolumeRenderWidget::setAABBScaleZ(int value)
{
    AABBScale.setZ(value / 300.0);
}

void VolumeRenderWidget::setIntensityCap(int value)
{
    intensityCap = value / 255.0;
}

float VolumeRenderWidget::fromRadian(float angle) {
    return angle * 180 / M_PI;
}

void VolumeRenderWidget::normalizeAngle(float &angle)
{
    while (angle < 0.0)
        angle += 360.0;
    while (angle > 360.0)
        angle -= 360.0;
}

void VolumeRenderWidget::setRotation(float angle, float& changeable) {
    normalizeAngle(angle);
    changeable = angle;
}

