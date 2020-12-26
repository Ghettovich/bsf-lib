#include "relay.h"

Relay::Relay(int relayId, IODevice::IO_DEVICE_HIGH_LOW _deviceState)
    : IODevice(relayId, _deviceState) {
}

bool Relay::isDeviceStateLOW() const {
  return deviceState == LOW;
}

bool Relay::isDeviceOn() const {
  return deviceState == LOW;
}
