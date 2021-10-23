#include "weightcensor.h"

WeightSensor::WeightSensor(int weightSensorId, IO_DEVICE_HIGH_LOW state) :
    IODevice(weightSensorId, state) {
}

bool WeightSensor::isDeviceOn() const {
  return getDeviceState() == HIGH;
}
int WeightSensor::getRecipeId() const {
  return recipeId;
}
int WeightSensor::getComponentId() const {
  return componentId;
}
int WeightSensor::getCurrentWeight() const {
  return currentWeight;
}
void WeightSensor::setRecipeId(int _recipeId) {
  recipeId = _recipeId;
}
void WeightSensor::setComponentId(int _componentId) {
  componentId = _componentId;
}
void WeightSensor::setCurrentWeight(int _currentWeight) {
  currentWeight = _currentWeight;
}
IODevice *WeightSensor::clone() const {
  return new WeightSensor(*this);
}

