#include "relay.h"

Relay::Relay(int relayId, IODevice::IO_DEVICE_HIGH_LOW _deviceState)
    : IODevice(relayId, _deviceState) {
}

bool Relay::isDeviceOn() const {
  return deviceState == LOW;
}
IODevice *Relay::clone() const {
  return new Relay(*this);
}
