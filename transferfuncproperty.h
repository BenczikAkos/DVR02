#pragma once
#include "transferfunckey.h"
#include "qopenglextrafunctions.h"

class TransferFuncProperty : public QObject {
	Q_OBJECT
public:
	TransferFuncProperty();
	QVector<float> getAllIntensities() const;
	QVector<float> getAllOpacities() const;
	QVector<QColor> getAllColors() const;
public slots:
	void intensityOpacityChangedAt(int index, float newIntensity, float newOpacity);
	void colorChangedAt(int index, QColor newColor);
private:
	void updateTFTexture();
	void getBlendedColors(float coeff, QColor c1, QColor c2, int& final_red, int& final_green, int& final_blue, int& final_alpha);
	void init_keys();
	QVector<std::shared_ptr<TransferFuncKey>> keys;
};