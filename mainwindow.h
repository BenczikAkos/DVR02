#pragma once

#include "qmainwindow.h"
#include "volumerenderwidget.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
    VolumeRenderWidget *canvas;
	//MainWindow::MainWindow* ui;
};

