#include "mixrecipeappservice.h"

using namespace appservice;
using namespace service;

MixRecipeAppService::MixRecipeAppService(std::shared_ptr<IODeviceService> &_deviceService, QObject *parent) :
    deviceService(_deviceService), QObject(parent) {

  auto iodevices = deviceService->getIODevices(IODeviceType::DETECTIONSENSOR);

  for(auto device : iodevices) {
    qDebug() << device->getDescription();
  }
}
