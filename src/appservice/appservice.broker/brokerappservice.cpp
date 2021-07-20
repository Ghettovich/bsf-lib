#include "brokerappservice.h"

using namespace appservice;
using namespace service;

BrokerAppService::BrokerAppService(std::shared_ptr<service::BrokerService> &_brokerService,
                                   std::shared_ptr<IODeviceService> &_deviceService,
                                   QObject *parent) :
    brokerService(_brokerService), deviceService(_deviceService), QObject(parent) {

  connect(brokerService.get(), &BrokerService::connectedToHost, [=]() {
    emit connectedToHost();
  });

  connect(deviceService.get(), &IODeviceService::updateRelayDevices, [=](const QVector<IODevice *> &devices) {
    emit updateDevicesWithState(devices);
  });

  connect(deviceService.get(), &IODeviceService::updateProximityDevices, [=](const QVector<IODevice *> &devices) {
    emit updateDevicesWithState(devices);
  });

  connect(deviceService.get(), &IODeviceService::updateScale, [=](IODevice *device) {
    emit updateDeviceWithState(device);
  });
}
QVector<IODevice *> BrokerAppService::findAll(IODeviceType::IO_DEVICE_TYPE type) {
  return deviceService->getIODevices(type);
}
void BrokerAppService::connectToHost() {
  brokerService->connectToHost();
}
void BrokerAppService::createDeviceStateSubscriptions() {
  deviceService->createDeviceStateSubscriptions();
}
void BrokerAppService::toggleRelay(int id) {
  brokerService->toggleRelay(id);
}
void BrokerAppService::configureRecipe(int recipeId, int componentId, int targetWeight) {
  brokerService->configureRecipe(recipeId, componentId, targetWeight);
}