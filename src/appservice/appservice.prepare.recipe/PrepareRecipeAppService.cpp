#include "PrepareRecipeAppService.h"
#include <QDebug>


using namespace appservice;

PrepareRecipeAppService::PrepareRecipeAppService(std::shared_ptr<IODeviceService> &_deviceService, QObject *parent) :
    deviceService(_deviceService), QObject(parent) {

  auto iodevices = deviceService->getIODevices(IODeviceType::DETECTIONSENSOR);

  for(auto device : iodevices) {
    qDebug() << device->getDescription();
  }
}
