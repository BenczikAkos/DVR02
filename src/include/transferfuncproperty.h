#pragma once
#include "transferfunckey.h"
#include "qopenglextrafunctions.h"

class TransferFuncProperty : public QObject, protected QOpenGLExtraFunctions {
	Q_OBJECT
public:
	TransferFuncProperty(GLuint _loc);
	QVector<float> getAllIntensities() const;
	QVector<float> getAllOpacities() const;
	QVector<QColor> getAllColors() const;
	void addKey(float _intensity, const QColor& _color);
	void removeKeyAt(int _index);
	bool isTransparent(int value, float intensityMin);
	void bind();
public slots:
	void intensityOpacityChangedAt(int index, float newIntensity, float newOpacity);
	void colorChangedAt(int index, QColor newColor);
private:
	void updateTFTexture();
	void getBlendedColors(float coeff, QColor c1, QColor c2, unsigned char& final_red, unsigned char& final_green, unsigned char& final_blue, unsigned char& final_alpha);
	void init_keys();
	QVector<std::shared_ptr<TransferFuncKey>> keys;
	unsigned char colorMap[256 * 4];
	GLuint textureLocation = 0;
};