
#include "volumerenderwindow.h"
#include <QKeyEvent>

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
    LocCameraPos = m_program->uniformLocation("cameraPos");
    Q_ASSERT(LocCameraPos != -1);
    LocWindowSize = m_program->uniformLocation("WindowSize");
    Q_ASSERT(LocWindowSize != -1);

    CameraPos = QVector3D(0.0f, 0.0f, -3.0f);
}

void VolumeRenderWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    /*QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    viewMatrix.rotate(m_yRot / 16.0f, 0, 1, 0);
    viewMatrix.rotate(m_zRot / 16.0f, 0, 0, 1);*/
    m_program->setUniformValue(LocViewMatrix, viewMatrix);

    m_program->setUniformValue(LocCameraPos, CameraPos);

    QVector2D windowSize = QVector2D(this->width(), this->height());
    m_program->setUniformValue(LocWindowSize, windowSize);

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glEnableVertexAttribArray(m_posAttr);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;
}

void VolumeRenderWindow::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
    case Qt::Key_A:
        CameraPos += QVector3D(-0.01f, 0.0f, 0.0f) * viewMatrix; break;
    case Qt::Key_D:
        CameraPos += QVector3D(0.01f, 0.0f, 0.0f) * viewMatrix; break;
    case Qt::Key_Q:
        CameraPos += QVector3D(0.0f, 0.01f, 0.0f) * viewMatrix; break;
    case Qt::Key_E:
        CameraPos += QVector3D(0.0f, -0.01f, 0.0f) * viewMatrix; break;
    case Qt::Key_W:
        CameraPos += QVector3D(0.0f, 0.0f, 0.01f) * viewMatrix; break;
    case Qt::Key_S:
        CameraPos += QVector3D(0.0f, 0.0f, -0.01f) * viewMatrix; break;
    }
}

void VolumeRenderWindow::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}


void VolumeRenderWindow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setZRotation(m_zRot + 8 * dx);
    }
    viewMatrix.setToIdentity();
    viewMatrix.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    viewMatrix.rotate(m_yRot / 16.0f, 0, 1, 0);
    viewMatrix.rotate(m_zRot / 16.0f, 0, 0, 1);
    m_lastPos = event->pos();
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
    if (angle != m_xRot) {
        m_xRot = angle;
    }
}

void VolumeRenderWindow::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
    }
}

void VolumeRenderWindow::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
    }
}
