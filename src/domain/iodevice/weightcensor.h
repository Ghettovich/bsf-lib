#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include "iodevice.h"
#include <QObject>
#include <QMetaType>
#include <component/component.h>

class WeightSensor : public IODevice {
 Q_GADGET

 public:
  explicit WeightSensor(int weightSensorId = 0, IO_DEVICE_HIGH_LOW state = LOW);
  WeightSensor(int weightSensorId, int recipeId, int componentId, int currentWeight = 0, IO_DEVICE_HIGH_LOW state = LOW);
  int getRecipeId() const;
  void setRecipeId(int recipeId);
  int getComponentId() const;
  void setComponentId(int componentId);
  int getCurrentWeight() const;
  void setCurrentWeight(int currentWeight);
  bool isDeviceOn() const override;

 private:
  int recipeId = 0;
  int componentId = 0;
  int currentWeight = 0;
};

#endif // WEIGHTCENSOR_H
