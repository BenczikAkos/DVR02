#pragma once

#include "qmainwindow.h"
#include "volumedatareader.h"
#include "QtCore/qdeadlinetimer.h"
#include "transferfunceditordialog.h"
#include "visualizationsetting.h"
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
	VolumeDataReader* getReader() const;
	QChart* generateChart() const;
	void initializeContext();

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
	void on_transferFunctionButton_clicked(bool checked);
	void on_intensityMaxSlider_valueChanged(int value);
	void on_intensityMinSlider_valueChanged(int value);

private:
	void connectVolumeDataReaderSlots();
	void populateModesComboBox();
	void populateDataTypesComboBox();
	float normalizeSliderValue(const QSlider& slider, int value) const;
	int lastPaint = 0;
	QDeadlineTimer updateFrameRateTimer = QDeadlineTimer();
	Ui::MainWindow* ui;
	std::unique_ptr<VolumeDataReader> reader = nullptr;
	std::shared_ptr<VisualizationSetting> visualizationSetting = nullptr;
};

