#ifndef BSF_DETECTIONSENSOR_H
#define BSF_DETECTIONSENSOR_H

#include "iodevice.h"

class DetectionSensor : public IODevice {

 public:
  DetectionSensor(int id, IO_DEVICE_HIGH_LOW deviceState);
  bool isDeviceStateLOW() const override;
  bool isDeviceOn() const override;
};

#endif //BSF_DETECTIONSENSOR_H
