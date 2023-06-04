#pragma once

#include "qmainwindow.h"
#include "QtCore/qdeadlinetimer.h"
#include <QChart>
#include <QSlider>


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
	QChart* generateChart() const;
	~MainWindow();

signals:
	void AABBChangedX(float value);
	void AABBChangedY(float value);
	void AABBChangedZ(float value);
	void intensityMaxChanged(int value);
	void intensityMinChanged(int value);

private slots:
	void on_AABBScale_x_valueChanged(int value);
	void on_AABBScale_y_valueChanged(int value);
	void on_AABBScale_z_valueChanged(int value);
	void on_loadVolumeButton_clicked(bool checked);
	void on_chartButton_clicked(bool checked);
	void on_intensityMaxSlider_valueChanged(int value) { emit intensityMaxChanged(value); }
	void on_intensityMinSlider_valueChanged(int value) { emit intensityMinChanged(value); }

private:
	float normalizeSliderValue(const QSlider& slider, int value) const;
	int lastPaint = 0;
	QDeadlineTimer updateFrameRateTimer = QDeadlineTimer();
	Ui::MainWindow* ui;
};

