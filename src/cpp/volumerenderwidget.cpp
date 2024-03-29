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
    auto program = visualizationSetting->getActiveProgram();
    m_posAttr = program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);



    GLuint VolumeLocation = program->uniformLocation("Volume");
    volume = std::make_shared<VolumeData>(VolumeLocation, mainWindow->getReader());
    boundingGeometry = std::make_shared<BoundingGeometry>(volume, visualizationSetting);

    glGenBuffers(1, &BoundingEBO);
    Q_ASSERT(BoundingEBO != -1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BoundingEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), boundingGeometry->getIndices(), GL_STATIC_DRAW);


    glGenBuffers(1, &QuadEBO);
    Q_ASSERT(QuadEBO != -1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), quadIndices.constData(), GL_STATIC_DRAW);


    generateFBO(enterFBO, enterTexture);
    generateFBO(exitFBO, exitTexture);
}

void VolumeRenderWidget::paintGL()
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const qreal retinaScale = devicePixelRatio();
    //enter pass
    glBindFramebuffer(GL_FRAMEBUFFER, enterFBO);
        glClearDepthf(1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
	    auto PARCProgram = visualizationSetting->getPARCProgram();
	    if (!PARCProgram->bind()) 
	    {
		    qWarning() << "PARC program not bound!";
	    };

	    PARCProgram->setUniformValue("ViewMatrix", ViewMatrix);
        drawBoundingGeometry();
	    PARCProgram->release();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //exit pass
    glBindFramebuffer(GL_FRAMEBUFFER, exitFBO);
        glClearDepthf(0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);
        if (!PARCProgram->bind())
        {
            qWarning() << "PARC program not bound!";
        };
        PARCProgram->setUniformValue("ViewMatrix", ViewMatrix);
        drawBoundingGeometry();
        PARCProgram->release();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // render pass
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    auto program = visualizationSetting->getActiveProgram();
    if (!program->bind()) 
    {
        qWarning() << "Program not bound!";
    };

    program->setUniformValue("WindowSize", windowSize * retinaScale);
    program->setUniformValue("CameraPos", CameraPos);   
    program->setUniformValue("enterTexture", 1);
    program->setUniformValue("exitTexture", 2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, enterTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, exitTexture);
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
        boundingGeometry->update();
    }
}

QChart* VolumeRenderWidget::generateChart() const
{
    return volume->createChart();
}

void VolumeRenderWidget::mousePressEvent(QMouseEvent *event)
{
    mouse_lastPos = event->pos();
}

void VolumeRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - mouse_lastPos.x();
    int dy = event->y() - mouse_lastPos.y();

    if (event->buttons() & Qt::RightButton) {
        phi -= (float)dx / 40;
        elevation += (float)dy / 40;
        //rotateScene(phi, elevation);
    }
    updateViewMatrix();
    mouse_lastPos = event->pos();
}

void VolumeRenderWidget::wheelEvent(QWheelEvent* event) {
    distance += event->angleDelta().y() / 100.0f;
    updateViewMatrix();
}

void VolumeRenderWidget::resizeEvent(QResizeEvent* event)
{
    QOpenGLWidget::resizeEvent(event);
    windowSize = QSize(this->width(), this->height());
    generateFBO(enterFBO, enterTexture);
    generateFBO(exitFBO, exitTexture);
}

void VolumeRenderWidget::rotateScene(float phi, float theta){
    QVector3D origo = QVector3D(0.0f, 0.0f, 0.0f);
    float radius = CameraPos.distanceToPoint(origo);

    CameraPos.setX(radius * cos(phi) * cos(theta));
    CameraPos.setY(radius * sin(theta));
    CameraPos.setZ(radius * sin(phi) * cos(theta));
}

float VolumeRenderWidget::fromRadian(float angle) {
    return angle * 180 / M_PI;
}

void VolumeRenderWidget::generateFBO(GLuint& fbo, GLuint& tex)
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    auto wreal = width() * devicePixelRatio();
    auto hreal = height() * devicePixelRatio();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, wreal, hreal, 0, GL_RGB, GL_FLOAT, NULL);
    qDebug() << "wreal: " << wreal << " hreal: " << hreal <<" fbo: " << fbo <<" tex: " << tex;
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

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

void VolumeRenderWidget::updateViewMatrix()
{
    CameraPos.setX(distance * cos(phi) * cos(elevation));
    CameraPos.setY(distance * sin(elevation));
    CameraPos.setZ(distance * sin(phi) * cos(elevation));
    ViewMatrix.setToIdentity();
    ViewMatrix.perspective(45.0f, 1.0f, 0.1f, 100.0f);
    ViewMatrix.lookAt(CameraPos, QVector3D(0.5f, 0.5f, 0.5f), QVector3D(0.0f, 1.0f, 0.0f));
}

void VolumeRenderWidget::drawQuad()
{
    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, quadVertices.constData());
    glEnableVertexAttribArray(m_posAttr);
    glBindVertexArray(m_posAttr);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, quadIndices.size() * sizeof(GLuint), quadIndices.constData(), GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, quadIndices.size(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(m_posAttr);
}

void VolumeRenderWidget::drawBoundingGeometry()
{
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, boundingGeometry->getVertices());
    glEnableVertexAttribArray(m_posAttr);
    glBindVertexArray(m_posAttr);
    auto nbOfIndices = boundingGeometry->getIndexCount();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BoundingEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbOfIndices * sizeof(GLuint), boundingGeometry->getIndices(), GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, nbOfIndices, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(m_posAttr);
}

void VolumeRenderWidget::normalizeAngle(float &angle)
{
    while (angle < 0.0)
        angle += 360.0;
    while (angle > 360.0)
        angle -= 360.0;
}

