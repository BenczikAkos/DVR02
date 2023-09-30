#include "transferfuncproperty.h"


TransferFuncProperty::TransferFuncProperty() {
	init_keys();
}

const QVector<float> TransferFuncProperty::getAllIntensities() const
{
	auto res = QVector<float>();
	res.reserve(keys.size());
	std::transform(keys.begin(), keys.end(), std::back_inserter(res),
		[](std::shared_ptr<TransferFuncKey> key) { return key->intensity; });
	return res;
}

const QVector<float> TransferFuncProperty::getAllOpacities() const
{
	auto res = QVector<float>();
	res.reserve(keys.size());
	std::transform(keys.begin(), keys.end(), std::back_inserter(res),
		[](std::shared_ptr<TransferFuncKey> key) { return key->color.alpha(); });
	return res;
}

void TransferFuncProperty::init_keys()
{
	QVector<int> randomIntensities = { 0, 100, 110, 120, 120, 240, 255 };
	for (auto i : randomIntensities) {
		keys.append(std::make_shared<TransferFuncKey>(i, QColor(100, 10, 200, i)));
	}
		

}
