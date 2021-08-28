#include "pavement.controller.h"

#include <broker/BrokerService.h>
#include <database/DatabaseService.h>
#include <state/stateservice.h>

#include <widgets/home/home.h>
#include <widgets/experimental/experimental.h>

using namespace appservice;
using namespace service;

PavementController::PavementController(QObject *parent) : QObject(parent) {
  auto databaseService = std::make_shared<DatabaseService>();
  auto brokerService = std::make_shared<BrokerService>();

  auto deviceService = std::make_shared<IODeviceService>(databaseService, brokerService);
  auto stateService = std::make_shared<StateService>(brokerService, deviceService);

  brokerAppService = std::make_shared<BrokerAppService>(brokerService, stateService);
  deviceAppService = std::make_shared<IODeviceAppService>(brokerService, deviceService);

  qDebug() << "service count = " << deviceService.use_count();

  brokerAppService->connectToHost();

  connect(brokerAppService.get(), &BrokerAppService::connectedToHost, [=]() {
    brokerAppService->createDeviceStateSubscriptions();
  });
}

void PavementController::createStackedWidget(QLayout *layout) {
  stackedWidget = new QStackedWidget();

  stackedWidget->addWidget(new Home(stackedWidget));
  stackedWidget->addWidget(new QWidget); // ToDo: replace with new mixture
  stackedWidget->addWidget(new Experimental(deviceAppService, stackedWidget));

  layout->addWidget(stackedWidget);
}
void PavementController::updateCurrentWidget(int widgetNr) {
  stackedWidget->setCurrentIndex(widgetNr);
}
