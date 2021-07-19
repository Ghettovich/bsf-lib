#include "detectionsensor.h"

DetectionSensor::DetectionSensor(int detectionSensorId, IODevice::IO_DEVICE_HIGH_LOW deviceState)
    :
    IODevice(detectionSensorId, deviceState) {

}

bool DetectionSensor::isDeviceOn() const {
  return deviceState == LOW;
}
