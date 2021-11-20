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
  }
}
bool IODeviceService::isDeviceOn(int deviceId) {
  if(!deviceMap.contains(deviceId)) {
    qWarning() << "Could not find deviceId " << deviceId << " in device map";
    return false;
  }

  return deviceMap.value(deviceId)->isDeviceOn();
}
bool IODeviceService::isBinAtDrop() {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("detectionsensor");

  bool proximityBinDrop = isDeviceOn(settings->value("bindrop").toInt());
  bool proximityBinLoad = isDeviceOn(settings->value("binload").toInt());

  if(proximityBinDrop && !proximityBinLoad) {
    return true;
  }

  return false;
}
bool IODeviceService::isBinAtLoad() {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("detectionsensor");

  bool proximityBinDrop = isDeviceOn(settings->value("bindrop").toInt());
  bool proximityBinLoad = isDeviceOn(settings->value("binload").toInt());

  if(!proximityBinDrop && proximityBinLoad) {
    return true;
  }

  return false;
}
bool IODeviceService::isBinAtTop() {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("detectionsensor");

  bool proximityLiftTop = isDeviceOn(settings->value("lifttop").toInt());
  bool proximityLiftBottom = isDeviceOn(settings->value("liftbottom").toInt());

  if(proximityLiftTop && !proximityLiftBottom) {
    return true;
  }

  return false;
}
