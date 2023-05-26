#pragma once

#include "qmainwindow.h"
#include "QtCore/qdeadlinetimer.h"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	void paintEvent(QPaintEvent* event) override;
	QVector3D getDataSizes() const;
	~MainWindow();

private:
	int lastPaint = 0;
	QDeadlineTimer updateFrameRateTimer = QDeadlineTimer();
    //VolumeRenderWidget *canvas;
	Ui::MainWindow* ui;
};

