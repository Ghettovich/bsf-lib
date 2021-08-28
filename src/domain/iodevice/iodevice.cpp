#include "iodevice.h"
#include <QMetaEnum>

IODevice::IODevice(int id, IODevice::IO_DEVICE_HIGH_LOW deviceState)
    :
    iodeviceId(id), deviceState(deviceState) {
}

int IODevice::getId() const {
  return iodeviceId;
}

QString IODevice::getDescription() const {
  return description;
}

void IODevice::setDescription(const QString &_description) {
  description = _description;
}

IODevice::IO_DEVICE_HIGH_LOW IODevice::getDeviceState() const {
  return deviceState;
}

void IODevice::setDeviceState(IODevice::IO_DEVICE_HIGH_LOW _deviceState) {
  deviceState = _deviceState;
}

void IODevice::setDeviceType(IODeviceType::IO_DEVICE_TYPE _deviceType) {
  deviceType = _deviceType;
}

IODeviceType::IO_DEVICE_TYPE IODevice::getDeviceType() {
  return deviceType;
}

bool IODevice::isStateChanged(IODevice::IO_DEVICE_HIGH_LOW newState) {
  return deviceState != newState;
}
