#include "weightcensor.h"
#include <utility>

WeightSensor::WeightSensor(int weightSensorId, IO_DEVICE_HIGH_LOW state) :
    IODevice(weightSensorId, state) {
}

bool WeightSensor::isDeviceStateLOW() const {
  return getDeviceState() == LOW;
}

bool WeightSensor::isDeviceOn() const {
  return getDeviceState() == HIGH;
}

void WeightSensor::setComponent(Component c) {
  component = std::move(c);
}

Component WeightSensor::getComponent() const {
  return component;
}

