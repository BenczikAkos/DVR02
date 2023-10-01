#include "transferfuncproperty.h"


TransferFuncProperty::TransferFuncProperty() 
{
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

const QVector<QColor> TransferFuncProperty::getAllColors() const
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
	float TFTable[256*4];
	for (auto key = keys.begin(); key != std::prev(keys.end()); ++key)
	{
		auto currKey = key->get();
		auto nextKey = std::next(key)->get();
		float range = nextKey->intensity - currKey->intensity;
		for (int x = currKey->intensity; x < nextKey->intensity; ++x)
		{
			int step = x - (int)currKey->intensity;
			float coeff = step / range;
			float final_red = 0.0; float final_green = 0.0; float final_blue = 0.0; float final_alpha = 0.0;
			getBlendedColors(coeff, currKey->color, nextKey->color, final_red, final_green, final_blue, final_alpha);
			TFTable[x * 4 + 0] = final_red;
			TFTable[x * 4 + 1] = final_green;
			TFTable[x * 4 + 2] = final_blue;
			TFTable[x * 4 + 3] = final_alpha;
		}
	}
	for (size_t i = 0; i < 100; i++)
	{
		qWarning() << TFTable[i*4 + 3];
	}
}

void TransferFuncProperty::getBlendedColors(float coeff, QColor c1, QColor c2, float& final_red, float& final_green, float& final_blue, float& final_alpha)
{
	float r1 = c1.redF(); float g1 = c1.greenF(); float b1 = c1.blueF(); float a1 = c1.alphaF();
	float r2 = c2.redF(); float g2 = c2.greenF(); float b2 = c2.blueF(); float a2 = c2.alphaF();
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
		keys.append(std::make_shared<TransferFuncKey>(i, QColor(i, 10, 200, i)));
	}
		

}
