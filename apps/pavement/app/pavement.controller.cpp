#include "pavement.controller.h"

#include <broker/BrokerService.h>
#include <database/DatabaseService.h>
#include <state/stateservice.h>
#include <statemachine/machine.service.h>

#include <widgets/home/home.h>
#include <widgets/experimental/experimental.h>
#include <widgets/recipe/RecipeWidget.h>

using namespace appservice;
using namespace service;

PavementController::PavementController(QObject *parent) : QObject(parent) {
  auto uiService = std::make_shared<UiService>();

  auto databaseService = std::make_shared<DatabaseService>();
  auto brokerService = std::make_shared<BrokerService>();

  auto recipeService = std::make_shared<RecipeService>(databaseService);

  auto deviceService = std::make_shared<IODeviceService>(databaseService);
  auto stateService = std::make_shared<StateService>(brokerService, deviceService);

  auto stateMachineService = std::make_shared<MachineService>();

  brokerAppService = std::make_shared<BrokerAppService>(brokerService, stateService);
  deviceAppService = std::make_shared<IODeviceAppService>(deviceService);
  statemachineAppService = std::make_shared<StateMachineAppService>(brokerService, deviceService, stateMachineService);
  recipeAppService = std::make_shared<PrepareRecipeAppService>(deviceService, recipeService);
  uiAppService = std::make_shared<UiAppService>(uiService);

  qDebug() << "service count = " << deviceService.use_count();

  brokerAppService->connectToHost();

  connect(deviceAppService.get(), &IODeviceAppService::updateIODeviceState,
          uiAppService.get(), &UiAppService::onUpdateWidget);

  connect(deviceAppService.get(), &IODeviceAppService::updateScale,
          uiAppService.get(), &UiAppService::onUpdateScaleWidget);

  connect(uiAppService.get(), &UiAppService::toggleRelay,
          brokerAppService.get(), &BrokerAppService::onToggleRelay);
}

void PavementController::createStackedWidget(QLayout *layout) {
  stackedWidget = new QStackedWidget();

  auto home = new Home(deviceAppService, stackedWidget);
  stackedWidget->addWidget(home);

  mixtureWidget = new Mixture(deviceAppService, recipeAppService, brokerAppService, stackedWidget);
  stackedWidget->addWidget(mixtureWidget);
  uiAppService->addWidget(mixtureWidget->deviceWidgets());

  QObject::connect(mixtureWidget, &Mixture::stackedWidgetIndexChanged, [=](int previousIndex) {
    mixtureWidgetPreviousIndex = previousIndex;
  });

  auto experimental = new Experimental(deviceAppService, statemachineAppService, stackedWidget);
  stackedWidget->addWidget(experimental);
  uiAppService->addWidget(experimental->deviceWidgets());

  auto recipes = new RecipeWidget(recipeAppService);
  stackedWidget->addWidget(recipes);

  layout->addWidget(stackedWidget);
}
void PavementController::updateCurrentWidget(int widgetNr) {
  stackedWidget->setCurrentIndex(widgetNr);
}
void PavementController::updateMixtureWidget() {
  mixtureWidget->setStackedWidgetIndex(mixtureWidgetPreviousIndex);
}
