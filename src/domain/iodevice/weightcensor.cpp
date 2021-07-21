#include "weightcensor.h"

WeightSensor::WeightSensor(int weightSensorId, IO_DEVICE_HIGH_LOW state) :
    IODevice(weightSensorId, state) {
}

WeightSensor::WeightSensor(int weightSensorId,
                           int _recipeId,
                           int _componentId,
                           int _currentWeight,
                           IODevice::IO_DEVICE_HIGH_LOW state)
    :
    IODevice(weightSensorId, state), recipeId(_recipeId), componentId(_componentId), currentWeight(_currentWeight) {
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

