#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include "recipe.h"
#include "iodevice.h"
#include "component.h"
#include <QObject>

class WeightSensor: public IODevice
{
Q_GADGET

public:
    WeightSensor(Component component);
    int getCurrentWeightForComponent() const;
    void setCurrentWeightForComponent(int weight);
    void updateRecipeWithComponentData(int, int);
    bool isDeviceStateLOW() const override;
    bool isDeviceOn() const override;

private:
    Component component;
};

#endif // WEIGHTCENSOR_H
