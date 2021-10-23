#include "iodeviceservice.h"

#include "iodevice.h"
#include "detectionsensor.h"
#include "relay.h"
#include "weightcensor.h"

using namespace service;

IODeviceService::IODeviceService(std::shared_ptr<DatabaseService> _databaseService,
                                 QObject *parent) :
    QObject(parent),
    deviceRepository(std::make_unique<IODeviceRepository>(_databaseService, this)) {

  deviceMap = deviceRepository->findAllDevices();
}

std::shared_ptr<IODevice> IODeviceService::findDevice(int id) {
  return deviceMap.value(id);
}

QList<std::shared_ptr<IODevice>> IODeviceService::findAllDevices() {
  return deviceMap.values();
}
QList<std::shared_ptr<IODevice>> IODeviceService::findAllDevices(IODeviceType::IO_DEVICE_TYPE deviceType) {
  QList<std::shared_ptr<IODevice>> devicesWithType;

  for (const auto &device: deviceMap) {
    if (device->getDeviceType() == deviceType) {
      devicesWithType.append(device);
    }
  }

  return devicesWithType;
}

void IODeviceService::onUpdateIODeviceState(int deviceId, IODevice::IO_DEVICE_HIGH_LOW state) {
  if(!deviceMap.contains(deviceId)) {
    qWarning() << "Could not find deviceId " << deviceId << " in device map";
  }
  else {
    deviceMap.value(deviceId)->setDeviceState(state);
    emit stateChangdIODevice(deviceId, deviceMap.value(deviceId)->isDeviceOn());
  }
}

void IODeviceService::onUpdateScaleDevice(int deviceId, double weight) {
  if(!deviceMap.contains(deviceId)) {
    qWarning() << "Could not find deviceId " << deviceId << " in device map";
  }
  else {
    std::dynamic_pointer_cast<WeightSensor>(deviceMap.value(deviceId))->setCurrentWeight((int)weight);
    emit scaleChanged(deviceId, std::dynamic_pointer_cast<WeightSensor>(deviceMap.value(deviceId))->getCurrentWeight());
    qDebug() << "Received weight = " << std::dynamic_pointer_cast<WeightSensor>(deviceMap.value(deviceId))->getCurrentWeight();

  }
  // ToDo implement and act on state change scale
  // ToDo update current weight and emit scale data changes
}
bool IODeviceService::isDeviceOn(int deviceId) {
  if(!deviceMap.contains(deviceId)) {
    qWarning() << "Could not find deviceId " << deviceId << " in device map";
    return false;
  }

  return deviceMap.value(deviceId)->isDeviceOn();
}
