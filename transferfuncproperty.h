#pragma once
#include "transferfunckey.h"
#include "qopenglextrafunctions.h"

class TransferFuncProperty : public QObject {
	Q_OBJECT
public:
	TransferFuncProperty();
	const QVector<float> getAllIntensities() const;
	const QVector<float> getAllOpacities() const;
	const QVector<QColor> getAllColors() const;
public slots:
	void intensityOpacityChangedAt(int index, float newIntensity, float newOpacity);
	void colorChangedAt(int index, QColor newColor);
private:
	void updateTFTexture();
	void getBlendedColors(float coeff, QColor c1, QColor c2, float& final_red, float& final_green, float& final_blue, float& final_alpha);
	void init_keys();
	QVector<std::shared_ptr<TransferFuncKey>> keys;
};