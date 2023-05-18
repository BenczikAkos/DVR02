#pragma once

#include "qmainwindow.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

//private:
	//MainWindow::MainWindow* ui;
};

