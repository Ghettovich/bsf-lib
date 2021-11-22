#include "pavement.controller.h"

#include <widgets/home/home.h>
#include <widgets/experimental/experimental.h>
#include <widgets/recipe/RecipeWidget.h>

using namespace appservice;
using namespace service;

PavementController::PavementController(std::shared_ptr<IODeviceAppService> &_deviceAppService,
                                       std::shared_ptr<PrepareRecipeAppService> &_recipeAppService,
                                       std::shared_ptr<UiAppService> &_uiAppService,
                                       QObject *parent) :
    deviceAppService(_deviceAppService),
    recipeAppService(_recipeAppService),
    uiAppService(_uiAppService),
    QObject(parent) {
}

void PavementController::createStackedWidget(QLayout *layout) {
  stackedWidget = new QStackedWidget();

  tabWidgetCreateBatch = new TabWidgetCreateBatch(deviceAppService, recipeAppService, stackedWidget);
  stackedWidget->addWidget(tabWidgetCreateBatch);
  uiAppService->addWidget(tabWidgetCreateBatch->deviceWidgets());

  auto experimental = new Experimental(deviceAppService, stackedWidget);
  stackedWidget->addWidget(experimental);
  //uiAppService->addWidget(experimental->deviceWidgets());

  auto recipes = new RecipeWidget(recipeAppService);
  stackedWidget->addWidget(recipes);

  layout->addWidget(stackedWidget);
}
void PavementController::updateCurrentWidget(int widgetNr) {
  stackedWidget->setCurrentIndex(widgetNr);
}