#ifndef BSF_RELAY_H
#define BSF_RELAY_H

#include "iodevice.h"

class Relay : public IODevice {

 public:
  Relay(int relayId, IO_DEVICE_HIGH_LOW _deviceState);
  bool isDeviceOn() const override;
};

#endif //BSF_RELAY_H
