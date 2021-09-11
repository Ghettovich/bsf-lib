#ifndef BSF_IODEVICESERVICE_H_
#define BSF_IODEVICESERVICE_H_

#include "iodevice.h"
#include "iodevicetype.h"
#include "iodevicerepo.h"

#include <QObject>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <database/DatabaseService.h>
#include <broker/BrokerService.h>

class IODeviceService : public QObject {
 Q_OBJECT

 public:
  explicit IODeviceService(std::shared_ptr<service::DatabaseService> databaseService,
                           std::shared_ptr<service::BrokerService> &brokerService,
                           QObject *parent = nullptr);

  std::shared_ptr<IODevice> findDevice(int deviceId);
  QList<std::shared_ptr<IODevice>> findAllDevices();
  QList<std::shared_ptr<IODevice>> findAllDevices(IODeviceType::IO_DEVICE_TYPE deviceType);
  bool isDeviceOn(int deviceId);

 public slots:

  /// Update a device with a given @state.
  /// Depending on the device both LOW and HIGH could mean on.
  /// If a proximity (Pull-up) reports LOW its actually on. And, if a scale (digital) reports HIGH it is also on.
  void onUpdateIODeviceState(int deviceId, IODevice::IO_DEVICE_HIGH_LOW state);

 /// Update a scale device and their weight.
  void onUpdateScaleDevice(int deviceId, IODevice::IO_DEVICE_HIGH_LOW state, int recipeId, int componentId, int weight);

 private:
  QMap<int, std::shared_ptr<IODevice>> deviceMap;
  std::shared_ptr<IODeviceRepository> deviceRepository;
  std::shared_ptr<service::BrokerService> brokerService;

 signals:
  void stateChangdIODevice(int deviceId, bool on);
  void scaleChanged(int deviceId, bool on, int recipeId, int componentId, int weight);
};

#endif //BSF_IODEVICESERVICE_H_
