#include "mainwindow.h"

#include <QApplication>

#include <iodevice/iodeviceservice.h>
#include <recipe/recipeservice.h>
#include <recipe.selection/recipeselectionservice.h>

#include <broker/BrokerService.h>
#include <database/DatabaseService.h>
#include <state/stateservice.h>

#include <appservice.prepare.recipe/preparerecipeappservice.h>
#include <appservice.mix.recipe/mixrecipeappservice.h>
#include <appservice.broker/broker.appservice.h>

using namespace appservice;
using namespace service;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  auto databaseService = std::make_shared<DatabaseService>();
  auto brokerService = std::make_shared<BrokerService>();


  auto recipeService = std::make_shared<RecipeService>(databaseService);
  auto deviceService = std::make_shared<IODeviceService>(databaseService, brokerService);

  auto stateService = std::make_shared<StateService>(deviceService);

  auto recipeSelectionService = std::make_shared<RecipeSelectionService>(deviceService, recipeService);

  auto prepareRecipeAppService = std::make_shared<PrepareRecipeAppService>(deviceService, recipeService, recipeSelectionService);
  auto mixRecipeAppService = std::make_shared<MixRecipeAppService>(deviceService);
  auto brokerAppService = std::make_shared<BrokerAppService>(brokerService, deviceService, stateService);

  qDebug() << "service count = " << deviceService.use_count();

  brokerAppService->connectToHost();

  MainWindow w(prepareRecipeAppService, mixRecipeAppService, brokerAppService);

  w.setObjectName("Main");
  w.show();

  w.showSidebar();
  w.showStart();

  return QApplication::exec();
}

