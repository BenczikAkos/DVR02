#pragma once
#include "transferfunckey.h"
#include "qopenglextrafunctions.h"

class TransferFuncProperty {
	TransferFuncProperty();
private:
	void init_keys();
	QVector<std::shared_ptr<TransferFuncKey>> keys;
};