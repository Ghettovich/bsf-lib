#include "relay.h"

Relay::Relay(int id, IODevice::IO_DEVICE_HIGH_LOW deviceState) : IODevice(id, deviceState) {
}

bool Relay::isDeviceStateLOW() const {
    return getDeviceState() == LOW;
}
