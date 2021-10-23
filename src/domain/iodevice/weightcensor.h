#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include "iodevice.h"
#include <component/component.h>

class IODevice;

class WeightSensor : public IODevice {

 public:
  WeightSensor(int weightSensorId = 0, IO_DEVICE_HIGH_LOW state = LOW);
  int getRecipeId() const;
  void setRecipeId(int recipeId);
  int getComponentId() const;
  void setComponentId(int componentId);
  int getCurrentWeight() const;
  void setCurrentWeight(int currentWeight);

  bool isDeviceOn() const override;
  IODevice *clone() const override;

 private:
  int recipeId = 0;
  int componentId = 0;
  int currentWeight = 0;
};

#endif // WEIGHTCENSOR_H
