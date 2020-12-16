#include "weightcensor.h"
#include <utility>

WeightSensor::WeightSensor(Component _component)
{
    this->deviceState = HIGH;
    component = std::move(_component);
}
void WeightSensor::updateRecipeWithComponentData(int componentId, int weight)
{
    getRecipe().updateWeightForComponent(componentId, weight);
}
bool WeightSensor::isDeviceStateLOW() const
{
    return getDeviceState() == LOW;
}
bool WeightSensor::isDeviceOn() const
{
    return getDeviceState() == HIGH;
}
int WeightSensor::getCurrentWeightForComponent() const
{
    return component.getCurrentWeight();
}
void WeightSensor::setCurrentWeightForComponent(int weight)
{
    component.setCurrentWeight(weight);
}

