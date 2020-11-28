#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include "recipe.h"
#include "iodevice.h"
#include <QObject>

class WeightSensor : public IODevice
{
    Q_GADGET

public:
    WeightSensor(int, IO_DEVICE_HIGH_LOW);
    void updateRecipeWithComponentData(int, int);
    bool isDeviceStateLOW() const override;

//private:
//    Recipe recipe;
};

#endif // WEIGHTCENSOR_H
