#include "weightcensor.h"

WeightSensor::WeightSensor(int id, IODevice::IO_DEVICE_HIGH_LOW deviceState) : IODevice(id, deviceState) {
}

void WeightSensor::updateRecipeWithComponentData(int componentId, int weight) {
    getRecipe().updateWeightForComponent(componentId, weight);
}
bool WeightSensor::isDeviceStateLOW() const {
    return getDeviceState() == LOW;
}
