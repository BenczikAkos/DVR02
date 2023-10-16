#include "../include/volumerenderwidget.h"
#include <QKeyEvent>
#include <qfile.h>


VolumeRenderWidget::VolumeRenderWidget(QWidget* parent)
    : QOpenGLWidget {parent}
{
    setFocusPolicy(Qt::StrongFocus);
    mainWindow = (MainWindow*)(parentWidget()->parentWidget());
    update();
}

void VolumeRenderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    mainWindow->initializeContext();
    auto program = visualizationSetting->getActiveProgram().get();
    m_posAttr = program->attributeLocation("posAttr");
    glGenBuffers(1, &EBO);
    Q_ASSERT(m_posAttr != -1);

    GLuint VolumeLocation = program->uniformLocation("Volume");
    //Q_ASSERT(VolumeLocation != -1);
    volume = std::make_shared<VolumeData>(VolumeLocation, mainWindow->getReader());
    generateFBO();

}

void VolumeRenderWidget::paintGL()
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const qreal retinaScale = devicePixelRatio();

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    auto PARCProgram = visualizationSetting->getPARCProgram();
	    if (!PARCProgram->bind()) 
	    {
		    qWarning() << "PARC program not bound!";
	    };

	    PARCProgram->setUniformValue("ViewMatrix", ViewMatrix);
	    PARCProgram->setUniformValue("CameraPos", CameraPos);
	    PARCProgram->setUniformValue("WindowSize", windowSize * retinaScale);
        PARCProgram->setUniformValue("AABBScale", QVector3D(1.0f, 1.0f, 1.0f));
        PARCProgram->setUniformValue("stepLength", 0.001f);
	    drawQuad();
	    PARCProgram->release();
    QOpenGLFramebufferObject::bindDefault();

    auto program = visualizationSetting->getActiveProgram().get();
    if (!program->bind()) 
    {
        qWarning() << "Program not bound!";
    };

    program->setUniformValue("ViewMatrix", ViewMatrix);
    program->setUniformValue("CameraPos", CameraPos);
    program->setUniformValue("WindowSize", windowSize * retinaScale);
    program->setUniformValue("PARC", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, PARCTex);
    visualizationSetting->setUniforms();
    volume->bind();
    drawQuad();
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

void VolumeRenderWidget::resizeEvent(QResizeEvent* event)
{
    QOpenGLWidget::resizeEvent(event);
    windowSize = QSize(this->width(), this->height());
    generateFBO();
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

float VolumeRenderWidget::fromRadian(float angle) {
    return angle * 180 / M_PI;
}

void VolumeRenderWidget::generateFBO()
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenTextures(1, &PARCTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, PARCTex);
    auto wreal = width() * devicePixelRatio();
    auto hreal = height() * devicePixelRatio();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, wreal, hreal, 0, GL_RG, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, PARCTex, 0);

    GLenum attachments[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, attachments);

    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, wreal, hreal);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        qWarning() << "Framebuffer not complete!";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void VolumeRenderWidget::drawQuad()
{
    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, quadVertices);
    glEnableVertexAttribArray(m_posAttr);
    glBindVertexArray(m_posAttr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices.constData(), GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, quadIndices.size(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(m_posAttr);
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

