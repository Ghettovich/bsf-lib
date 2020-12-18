#include "weightcensor.h"
#include <utility>

WeightSensor::WeightSensor(int _id, IO_DEVICE_HIGH_LOW state) :
        IODevice(_id, state)
{
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
void WeightSensor::setComponent(Component c)
{
    component = std::move(c);
}
Component WeightSensor::getComponent() const
{
    return component;
}

