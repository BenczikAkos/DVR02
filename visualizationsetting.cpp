#include "visualizationsetting.h"

VisualizationSetting::VisualizationSetting() = default;

//void VisualizationSetting::setAABBScaleX(float value)
//{
//    AABBScale.setX(value);
//}
//
//void VisualizationSetting::setAABBScaleY(float value)
//{
//    AABBScale.setY(value);
//}
//
//void VisualizationSetting::setAABBScaleZ(float value)
//{
//    AABBScale.setZ(value);
//}
//
//void VisualizationSetting::setIntensityMax(int value)
//{
//    intensityMax = value / 255.0f;
//}
//
//void VisualizationSetting::setIntensityMin(int value)
//{
//    intensityMin = value / 255.0f;
//}
//
//void VisualizationSetting::setStepLength(double value)
//{
//    stepLength = value;
//}

void VisualizationSetting::setMode(int mode)
{
    CompositionMode _mode = static_cast<CompositionMode>(mode);
    activeMode = _mode;
}