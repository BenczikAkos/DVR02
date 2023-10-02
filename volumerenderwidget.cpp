#include "volumerenderwidget.h"
#include <QKeyEvent>
#include <qfile.h>


VolumeRenderWidget::VolumeRenderWidget(QWidget* parent)
    : QOpenGLWidget {parent}
{
    setFocusPolicy(Qt::StrongFocus);
    mainWindow = (MainWindow*)parentWidget()->parentWidget();
    update();
}

VolumeRenderWidget::~VolumeRenderWidget() = default;

void VolumeRenderWidget::createShaderProgram(Mode mode, const QString& vertexPath, const QString& fragmentPath)
{
    auto program = std::make_shared<QOpenGLShaderProgram>(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexPath);
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentPath);
    modes.insert(mode, program);
}

void VolumeRenderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    createShaderProgram(Mode::MIP, ":/vshader.glsl", ":/fshad_mip.glsl");
    createShaderProgram(Mode::Average, ":/vshader.glsl", ":/fshad_avg.glsl");
    createShaderProgram(Mode::Accumulate, ":/vshader.glsl", ":/fshad_accumulate.glsl");
    createShaderProgram(Mode::Isosurface, ":/vshader.glsl", ":/fshad_isosurface.glsl");
    QOpenGLShaderProgram* program = modes.value(activeMode).get();
    if(!program->link()){
        qWarning() << program->log();
    }

    m_posAttr = program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);

    GLuint VolumeLocation = program->uniformLocation("Volume");
    Q_ASSERT(VolumeLocation != -1);
    volume = std::make_shared<VolumeData>(VolumeLocation, mainWindow->getReader());

}

void VolumeRenderWidget::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);
    QOpenGLShaderProgram* program = modes.value(activeMode).get();
    if (!program->bind()) {
        qWarning() << "Program not bound!";
    };

    program->setUniformValue("ViewMatrix", ViewMatrix);
    program->setUniformValue("CameraPos", CameraPos);
    program->setUniformValue("AABBScale", AABBScale);
    volume->bind();
    //TODO: ne kerjuk már el minden frame-ben legyen tagvaltozo
    QVector2D windowSize = QVector2D(this->width(), this->height());
    program->setUniformValue("WindowSize", windowSize);
    program->setUniformValue("intensityMin", intensityMin);
    program->setUniformValue("intensityMax", intensityMax);
    program->setUniformValue("stepLength", stepLength);

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(m_posAttr);
    glBindVertexArray(m_posAttr);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(m_posAttr);

    program->release();
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
    Q_UNUSED(event)
    MouseFirstPressed = true;
}

void VolumeRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - mouse_lastPos.x();
    int dy = event->y() - mouse_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setRotation(xRot, xRot - dy);
        //setRotation(zRot - dy, zRot);
        setRotation(yRot, yRot + dx);
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
    setRotation(xRot, fromRadian(M_PI - theta));
    setRotation(yRot, fromRadian(M_PI / 2 - phi));
}

void VolumeRenderWidget::setAABBScaleX(float value)
{
    AABBScale.setX(value);
}

void VolumeRenderWidget::setAABBScaleY(float value)
{
    AABBScale.setY(value);
}

void VolumeRenderWidget::setAABBScaleZ(float value)
{
    AABBScale.setZ(value);
}

void VolumeRenderWidget::setIntensityMax(int value)
{
    intensityMax = value / 255.0f;
}

void VolumeRenderWidget::setIntensityMin(int value)
{
    intensityMin = value / 255.0f;
}

void VolumeRenderWidget::setStepLength(double value)
{
    stepLength = value;
}

void VolumeRenderWidget::setMode(int mode)
{
    Mode _mode = static_cast<Mode>(mode);
    activeMode = _mode;
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

void VolumeRenderWidget::setRotation(float& changeable, float angle) {
    normalizeAngle(angle);
    changeable = angle;
}

