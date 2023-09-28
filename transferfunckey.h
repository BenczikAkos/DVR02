#pragma once

#include <qcolor.h>

class TransferFuncKey {
public:
	TransferFuncKey(float _intensity = 0, QColor _color = QColor(0, 0, 0))
		: intensity(_intensity),
		color(_color){}
	float intensity;
	QColor color;
};