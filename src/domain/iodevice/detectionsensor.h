#ifndef BSF_DETECTIONSENSOR_H
#define BSF_DETECTIONSENSOR_H

#include "iodevice.h"

class DetectionSensor : public IODevice {

 public:
  DetectionSensor(int detectionSensorId, IO_DEVICE_HIGH_LOW deviceState);
  bool isDeviceOn() const override;
};

#endif //BSF_DETECTIONSENSOR_H
