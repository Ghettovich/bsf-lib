#ifndef APPSERVICE_IODEVICES_H_
#define APPSERVICE_IODEVICES_H_

#include <memory>
#include <QObject>
#include <iodevice/iodeviceservice.h>
#include <broker/BrokerService.h>
#include <state/stateservice.h>

namespace appservice {
class IODeviceAppService;
}

class appservice::IODeviceAppService : public QObject {
 Q_OBJECT

 public:
  explicit IODeviceAppService(std::shared_ptr<IODeviceService> &deviceService,
                              QObject *parent = nullptr);

  /// Find a device with a particular @deviceId
  std::shared_ptr<IODevice> findOne(int id);

  /// Get a list of all present devices.
  QList<std::shared_ptr<IODevice>> findAll();

  /// Get a list of all present devices with a given @deviceType
  QList<std::shared_ptr<IODevice>> findAll(IODeviceType::IO_DEVICE_TYPE type);

 private:
  std::shared_ptr<IODeviceService> deviceService;

 signals:
  /// Emit a signal that a device has changed and their state.
  /// Could either mean from HIGH to LOW or LOW to HIGH.
  void updateIODeviceState(int deviceId, bool on);

  /// Emit a signal that the weight of a scale got updated.
  void updateScale(int deviceId, int weight);
};

#endif //APPSERVICE_IODEVICES_H_
