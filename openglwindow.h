#pragma once

#include <QTWidgets/QMainWindow>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class OpenGLWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWidget *parent = nullptr);
    ~OpenGLWindow();

    virtual void render(QPainter *painter);
    virtual void render();

    virtual void initialize();

private:
    bool m_animating = false;

    QOpenGLContext *m_context = nullptr;
    QOpenGLPaintDevice *m_device = nullptr;
};