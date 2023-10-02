#include "transferfuncproperty.h"


TransferFuncProperty::TransferFuncProperty() 
{
	init_keys();
}

QVector<float> TransferFuncProperty::getAllIntensities() const
{
	auto res = QVector<float>();
	res.reserve(keys.size());
	std::transform(keys.begin(), keys.end(), std::back_inserter(res),
		[](std::shared_ptr<TransferFuncKey> key) { return key->intensity; });
	return res;
}

QVector<float> TransferFuncProperty::getAllOpacities() const
{
	auto res = QVector<float>();
	res.reserve(keys.size());
	std::transform(keys.begin(), keys.end(), std::back_inserter(res),
		[](std::shared_ptr<TransferFuncKey> key) { return key->color.alpha(); });
	return res;
}

QVector<QColor> TransferFuncProperty::getAllColors() const
{
	auto result = QVector<QColor>();
	result.reserve(keys.size());
	std::transform(keys.begin(), keys.end(), std::back_inserter(result),
		[](std::shared_ptr<TransferFuncKey> key) { auto res = key->color; res.setAlpha(255); return res; });
	return result;
}

void TransferFuncProperty::intensityOpacityChangedAt(int index, float newIntensity, float newOpacity)
{
	if (index == keys.size() - 1) 
	{
		newIntensity = 255;
	}
	if (index == 0)
	{
		newIntensity = 0;
	}
	auto changedKey = keys.at(index);
	changedKey->intensity = newIntensity;
	changedKey->color.setAlpha(newOpacity);
	updateTFTexture();
}

void TransferFuncProperty::colorChangedAt(int index, QColor newColor)
{
	auto changedKey = keys.at(index);
	changedKey->color = QColor(newColor.red(), newColor.green(), newColor.blue(), changedKey->color.alpha());
	updateTFTexture();
}

void TransferFuncProperty::updateTFTexture()
{
	int TFTable[256*4];
	for (auto key = keys.begin(); key != std::prev(keys.end()); ++key)
	{
		auto currKey = key->get();
		auto nextKey = std::next(key)->get();
		int range = (int)nextKey->intensity - (int)currKey->intensity;
		for (int x = currKey->intensity; x < nextKey->intensity; ++x)
		{
			float step = nextKey->intensity - x;
			float coeff = step / range;
			int final_red = 0.0; int final_green = 0.0; int final_blue = 0.0; int final_alpha = 0.0;
			getBlendedColors(coeff, currKey->color, nextKey->color, final_red, final_green, final_blue, final_alpha);
			qWarning() << x << "   " << final_red;
			TFTable[x * 4 + 0] = final_red;
			TFTable[x * 4 + 1] = final_green;
			TFTable[x * 4 + 2] = final_blue;
			TFTable[x * 4 + 3] = final_alpha;
		}
	}
}

void TransferFuncProperty::getBlendedColors(float coeff, QColor c1, QColor c2, int& final_red, int& final_green, int& final_blue, int& final_alpha)
{
	int r1 = c1.red(); int g1 = c1.green(); int b1 = c1.blue(); int a1 = c1.alpha();
	int r2 = c2.red(); int g2 = c2.green(); int b2 = c2.blue(); int a2 = c2.alpha();
	float oneMinusCoeff = 1.0f - coeff;
	final_red = coeff * r1 + oneMinusCoeff * r2;
	final_green = coeff * g1 + oneMinusCoeff * g2;
	final_blue = coeff * b1 + oneMinusCoeff * b2;
	final_alpha = coeff * a1 + oneMinusCoeff * a2;
}

void TransferFuncProperty::init_keys()
{
	QVector<int> randomIntensities = { 0, 100, 110, 120, 240, 255 };
	for (auto i : randomIntensities) 
	{
		keys.append(std::make_shared<TransferFuncKey>(i, QColor(100, 100, 100, 255)));
	}
		

}
