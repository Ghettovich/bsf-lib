#include "mainwindow.h"

#include <QApplication>

#include <iodevice/iodeviceservice.h>

#include <broker/BrokerService.h>
#include <database/DatabaseService.h>

#include <appservice.prepare.recipe/PrepareRecipeAppService.h>
#include <appservice.mix.recipe/MixRecipeAppService.h>
#include <appservice.broker/BrokerAppService.h>

using namespace appservice;
using namespace service;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  auto databaseService = std::make_shared<DatabaseService>();
  auto brokerService = std::make_shared<BrokerService>();

  auto deviceService = std::make_shared<IODeviceService>(databaseService, brokerService);

  auto prepareRecipeAppService = std::make_shared<PrepareRecipeAppService>(deviceService);
  auto mixRecipeAppService = std::make_shared<MixRecipeAppService>(deviceService);
  auto brokerAppService = std::make_shared<BrokerAppService>(brokerService, deviceService);

  qDebug() << "service count = " << deviceService.use_count();

  brokerAppService->connectToHost();

  MainWindow w(prepareRecipeAppService, mixRecipeAppService, brokerAppService);

  w.setObjectName("Main");
  w.show();

  w.showSidebar();
  w.showStart();

  return QApplication::exec();
}

