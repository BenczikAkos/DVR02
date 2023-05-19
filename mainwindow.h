#pragma once

#include "qmainwindow.h"
#include "volumerenderwidget.h"
#include "QtCore/qdeadlinetimer.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* event) override;
	~MainWindow();

private:
	int lastPaint = 0;
	QDeadlineTimer updateFrameRateTimer = QDeadlineTimer();
    VolumeRenderWidget *canvas;
	//MainWindow::MainWindow* ui;
};

