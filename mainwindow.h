#pragma once

#include "qmainwindow.h"
#include "QtCore/qdeadlinetimer.h"
#include <QtDebug>


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

signals:
	void AABBChangedX(int value);
	void AABBChangedY(int value);
	void AABBChangedZ(int value);

private slots:
	void on_AABBScale_x_valueChanged(int value) { emit AABBChangedX(value); }
	void on_AABBScale_y_valueChanged(int value) { emit AABBChangedY(value); }
	void on_AABBScale_z_valueChanged(int value) { emit AABBChangedZ(value); }

private:
	int lastPaint = 0;
	QDeadlineTimer updateFrameRateTimer = QDeadlineTimer();
	Ui::MainWindow* ui;
};

