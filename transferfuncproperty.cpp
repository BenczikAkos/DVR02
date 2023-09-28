#include "transferfuncproperty.h"


TransferFuncProperty::TransferFuncProperty() {
	init_keys();
}

void TransferFuncProperty::init_keys()
{
	QVector<int> randomIntensities = { 0, 100, 110, 120, 120, 240, 255 };
	for (auto i : randomIntensities) {
		keys.append(std::make_shared<TransferFuncKey>(i, QColor(100, 10, 200, i)));
	}
		

}
