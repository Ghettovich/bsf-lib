#include "detectionsensor.h"

DetectionSensor::DetectionSensor(int id, IODevice::IO_DEVICE_HIGH_LOW deviceState)
    :
    IODevice(id, deviceState)
{

}
bool DetectionSensor::isDeviceStateLOW() const
{
    return deviceState == LOW;
}
