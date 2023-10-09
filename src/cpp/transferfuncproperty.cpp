#include "../include/transferfuncproperty.h"


TransferFuncProperty::TransferFuncProperty(GLuint _loc) :
	textureLocation(_loc)
{
	init_keys();
	initializeOpenGLFunctions();
	updateTFTexture();
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

void TransferFuncProperty::addKey(float _intensity, const QColor& _color)
{
	for(auto key : keys)
	{
		if (key->intensity > _intensity)
		{
			keys.insert(keys.indexOf(key), std::make_shared<TransferFuncKey>(_intensity, _color));
			return;
		}
	}
}

void TransferFuncProperty::removeKeyAt(int _index)
{
	if (_index >= 0 && _index < keys.size()-1)
	{
		keys.remove(_index);
	}
}

void TransferFuncProperty::intensityOpacityChangedAt(int index, float newIntensity, float newOpacity)
{
	auto currKey = keys.at(index);
	if (index == keys.size() - 1) 
	{
		currKey->color.setAlpha(newOpacity);
		updateTFTexture();
		return;
	}
	else if (index == 0)
	{
		currKey->color.setAlpha(newOpacity);
		updateTFTexture();
		return;
	}
	else {
		auto left = keys.at(index - 1);
		auto right = keys.at(index + 1);
		if (newIntensity <= left->intensity)
		{
			newIntensity = left->intensity + 1.0;
		}
		if (newIntensity > right->intensity)
		{
			newIntensity = right->intensity - 1.0;
		}
		currKey->intensity = newIntensity;
		currKey->color.setAlpha(newOpacity);
		updateTFTexture();
	}
}

void TransferFuncProperty::colorChangedAt(int index, QColor newColor)
{
	auto changedKey = keys.at(index);
	changedKey->color = QColor(newColor.red(), newColor.green(), newColor.blue(), changedKey->color.alpha());
	updateTFTexture();
}

void TransferFuncProperty::updateTFTexture()
{
	unsigned char TFTable[256*4];
	for (auto key = keys.begin(); key != std::prev(keys.end()); ++key)
	{
		auto currKey = key->get();
		auto nextKey = std::next(key)->get();
		int range = (int)nextKey->intensity - (int)currKey->intensity;
		for (int x = currKey->intensity; x <= nextKey->intensity; ++x)
		{
			float step = nextKey->intensity - x;
			float coeff = step / range;
			unsigned char final_red = 0; unsigned char final_green = 0; unsigned char final_blue = 0; unsigned char final_alpha = 0;
			getBlendedColors(coeff, currKey->color, nextKey->color, final_red, final_green, final_blue, final_alpha);
			TFTable[x * 4 + 0] = final_red;
			TFTable[x * 4 + 1] = final_green;
			TFTable[x * 4 + 2] = final_blue;
			TFTable[x * 4 + 3] = final_alpha;
		}
	}

	glDeleteTextures(1, &textureLocation);
	glGenTextures(1, &textureLocation);
	glBindTexture(GL_TEXTURE_2D, textureLocation);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //tightly packed
	glPixelStorei(GL_UNPACK_LSB_FIRST, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &TFTable);
}

void TransferFuncProperty::getBlendedColors(float coeff, QColor c1, QColor c2, unsigned char& final_red, unsigned char& final_green, unsigned char& final_blue, unsigned char& final_alpha)
{
	unsigned char r1 = c1.red(); unsigned char g1 = c1.green(); unsigned char b1 = c1.blue(); unsigned char a1 = c1.alpha();
	unsigned char r2 = c2.red(); unsigned char g2 = c2.green(); unsigned char b2 = c2.blue(); unsigned char a2 = c2.alpha();
	float oneMinusCoeff = 1.0f - coeff;
	final_red = coeff * r1 + oneMinusCoeff * r2;
	final_green = coeff * g1 + oneMinusCoeff * g2;
	final_blue = coeff * b1 + oneMinusCoeff * b2;
	final_alpha = coeff * a1 + oneMinusCoeff * a2;
}

void TransferFuncProperty::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureLocation);
}

void TransferFuncProperty::init_keys()
{
	QVector<int> randomIntensities = { 0, 100, 110, 120, 240, 255 };
	for (auto i : randomIntensities) 
	{
		keys.append(std::make_shared<TransferFuncKey>(i, QColor(i, i, i, i)));
	}
		

}
