#include "broker.appservice.h"

using namespace appservice;
using namespace service;

BrokerAppService::BrokerAppService(std::shared_ptr<service::BrokerService> &_brokerService,
                                   std::shared_ptr<StateService> &_stateService,
                                   QObject *parent) :
    brokerService(_brokerService), stateService(_stateService), QObject(parent) {

  connect(brokerService.get(), &BrokerService::connectedToHost, [=]() {
    emit connectedToHost();
  });

  connect(this, &BrokerAppService::connectedToHost,
          this, &BrokerAppService::onCreateDeviceStateSubscriptions);
}

void BrokerAppService::connectToHost() {
  brokerService->connectToHost();
}
void BrokerAppService::onCreateDeviceStateSubscriptions() {
  stateService->createDeviceStateSubscriptions();
}
void BrokerAppService::onToggleRelay(int id) {
  brokerService->toggleRelay(id);
}
void BrokerAppService::configureRecipe(int recipeId, int componentId, int targetWeight) {
  brokerService->configureRecipe(recipeId, componentId, targetWeight);
}
