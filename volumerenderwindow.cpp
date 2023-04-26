
#include "volumerenderwindow.h"

void VolumeRenderWindow::initializeGL()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
    LocCameraPos = m_program->uniformLocation("cameraPos");
    Q_ASSERT(LocCameraPos != -1);
    LocWindowSize = m_program->uniformLocation("WindowSize");
    Q_ASSERT(LocWindowSize != -1);
}
//! [4]

//! [5]
void VolumeRenderWindow::paintGL()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.setToIdentity();
    m_program->setUniformValue(m_matrixUniform, matrix);

    QVector3D camera = QVector3D(0.0f, 0.0f, -3.0f);
    m_program->setUniformValue(LocCameraPos, camera);

    QVector2D windowSize = QVector2D(this->width(), this->height());
    m_program->setUniformValue(LocWindowSize, windowSize);

    static const GLfloat vertices[] = {
        1.0f,  1.0f,
        1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    };



    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glEnableVertexAttribArray(m_posAttr);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;
}

