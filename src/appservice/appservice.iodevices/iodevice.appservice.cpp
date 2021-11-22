#include "iodevice.appservice.h"

using namespace appservice;

IODeviceAppService::IODeviceAppService(std::shared_ptr<IODeviceService> &_deviceService,
                                       QObject *parent) :
    deviceService(_deviceService), QObject(parent) {

  connect(deviceService.get(), &IODeviceService::stateChangdIODevice, [=](int deviceId, bool on) {
    emit updateIODeviceState(deviceId, on);
  });
  connect(deviceService.get(), &IODeviceService::scaleChanged, [=](int deviceId, int weight) {
    emit updateScale(deviceId, weight);
  });
}

std::shared_ptr<IODevice> IODeviceAppService::findOne(int id) {
  return deviceService->findDevice(id);
}

QList<std::shared_ptr<IODevice>> IODeviceAppService::findAll() {
  return deviceService->findAllDevices();
}
QList<std::shared_ptr<IODevice>> IODeviceAppService::findAll(IODeviceType::IO_DEVICE_TYPE type) {
  return deviceService->findAllDevices(type);
}
bool IODeviceAppService::isLiftAtBottom() {
  return deviceService->isLiftAtBottom();
}
bool IODeviceAppService::isLiftAtTop() {
  return deviceService->isLiftAtTop();
}
