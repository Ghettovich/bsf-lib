#ifndef WEIGHTCENSOR_H
#define WEIGHTCENSOR_H

#include "iodevice.h"
#include "component.h"
#include <QObject>
#include <QMetaType>

class WeightSensor : public IODevice {
 Q_GADGET

 public:

  explicit WeightSensor(int weightSensorId = 0, IO_DEVICE_HIGH_LOW state = LOW);
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
