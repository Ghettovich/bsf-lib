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
    WeightSensor(int id, IO_DEVICE_HIGH_LOW state);
    void setComponent(Component c);
    Component getComponent() const;
    int getCurrentWeightForComponent() const;
    void setCurrentWeightForComponent(int weight);
    bool isDeviceStateLOW() const override;
    bool isDeviceOn() const override;

private:
    Component component;
};

#endif // WEIGHTCENSOR_H
