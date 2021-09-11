#include "pavement.controller.h"

#include <broker/BrokerService.h>
#include <database/DatabaseService.h>
#include <state/stateservice.h>

#include <widgets/home/home.h>
#include <widgets/experimental/experimental.h>

using namespace appservice;
using namespace service;

PavementController::PavementController(QObject *parent) : QObject(parent) {
  auto uiService = std::make_shared<UiService>();

  auto databaseService = std::make_shared<DatabaseService>();
  auto brokerService = std::make_shared<BrokerService>();

  auto deviceService = std::make_shared<IODeviceService>(databaseService, brokerService);
  auto stateService = std::make_shared<StateService>(brokerService, deviceService);

  brokerAppService = std::make_shared<BrokerAppService>(brokerService, stateService);
  deviceAppService = std::make_shared<IODeviceAppService>(deviceService);
  statemachineAppService = std::make_shared<StateMachineAppService>(brokerService, deviceService);
  uiAppService = std::make_shared<UiAppService>(uiService);

  qDebug() << "service count = " << deviceService.use_count();

  brokerAppService->connectToHost();

  connect(deviceAppService.get(), &IODeviceAppService::updateIODeviceState,
          uiAppService.get(), &UiAppService::onUpdateWidget);

  connect(uiAppService.get(), &UiAppService::toggleRelay,
          brokerAppService.get(), &BrokerAppService::onToggleRelay);
}

void PavementController::createStackedWidget(QLayout *layout) {
  stackedWidget = new QStackedWidget();

  auto home = new Home(deviceAppService, stackedWidget);
  stackedWidget->addWidget(home);

  stackedWidget->addWidget(new QWidget); // ToDo: replace with new mixture

  auto experimental = new Experimental(deviceAppService, statemachineAppService, stackedWidget);
  stackedWidget->addWidget(experimental);
  uiAppService->addWidget(experimental->deviceWidgets());

  layout->addWidget(stackedWidget);
}
void PavementController::updateCurrentWidget(int widgetNr) {
  stackedWidget->setCurrentIndex(widgetNr);
}
