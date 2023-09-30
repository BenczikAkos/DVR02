#pragma once
#include "transferfunckey.h"
#include "qopenglextrafunctions.h"

class TransferFuncProperty {
public:
	TransferFuncProperty();
	const QVector<float> getAllIntensities() const;
	const QVector<float> getAllOpacities() const;
	const QVector<QColor> getAllColors() const;
private:
	void init_keys();
	QVector<std::shared_ptr<TransferFuncKey>> keys;
};