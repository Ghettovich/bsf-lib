#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <broker/BrokerService.h>
#include <database/DatabaseService.h>
#include <state/stateservice.h>

#include <QtWidgets>

using namespace appservice;
using namespace service;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);

  auto uiService = std::make_shared<UiService>();

  auto databaseService = std::make_shared<DatabaseService>();
  auto brokerService = std::make_shared<BrokerService>();

  auto recipeService = std::make_shared<RecipeService>(databaseService);

  auto deviceService = std::make_shared<IODeviceService>(databaseService);
  auto stateService = std::make_shared<StateService>(brokerService, deviceService);

  brokerAppService = std::make_shared<BrokerAppService>(brokerService, stateService);
  deviceAppService = std::make_shared<IODeviceAppService>(deviceService);
  recipeAppService = std::make_shared<PrepareRecipeAppService>(deviceService, recipeService);
  uiAppService = std::make_shared<UiAppService>(uiService);

  qDebug() << "service count = " << deviceService.use_count();

  brokerAppService->connectToHost();

  initRelayListWidget();
  initProximitiesWidget();

  connect(deviceAppService.get(), &IODeviceAppService::updateIODeviceState,
          this, &MainWindow::onUpdateRelayListWidget);
  connect(deviceAppService.get(), &IODeviceAppService::updateIODeviceState,
          this, &MainWindow::onUpdateProximityListWidget);

  connect(deviceAppService.get(), &IODeviceAppService::updateIODeviceState,
          uiAppService.get(), &UiAppService::onUpdateWidget);

  connect(deviceAppService.get(), &IODeviceAppService::updateScale,
          uiAppService.get(), &UiAppService::onUpdateScaleWidget);

  connect(uiAppService.get(), &UiAppService::toggleRelay,
          brokerAppService.get(), &BrokerAppService::onToggleRelay);

  controller = std::make_unique<PavementController>(deviceAppService, recipeAppService, uiAppService);
  controller->createStackedWidget(ui->verticalLayoutMain);

  connect(ui->pushButtonBatch, &QPushButton::clicked, this, &MainWindow::onShowStart);
  connect(ui->pushButtonExperimental, &QPushButton::clicked, this, &MainWindow::onShowExperimental);
  connect(ui->pushButtonRecipes, &QPushButton::clicked, this, &MainWindow::onShowRecipes);
}

MainWindow::~MainWindow() {
  delete ui;
}
void MainWindow::onShowStart() {
  controller->updateCurrentWidget(0);
}
void MainWindow::onShowExperimental() {
  controller->updateCurrentWidget(1);
}
void MainWindow::onShowRecipes() {
  controller->updateCurrentWidget(2);
}
void MainWindow::onShowLogs() {
  controller->updateCurrentWidget(3);
}
void MainWindow::initRelayListWidget() {
  auto deviceList = deviceAppService->findAll(IODeviceType::RELAY);

  for (const auto &device :deviceList) {
    auto listWidgetItem = new QListWidgetItem(materialRegular.boltIcon(Qt::red), device->getDescription());
    listWidgetItem->setData(Qt::UserRole, device->getId());
    ui->listWidgetRelays->addItem(listWidgetItem);
  }
}
void MainWindow::initProximitiesWidget() {
  auto deviceList = deviceAppService->findAll(IODeviceType::DETECTIONSENSOR);

  for (const auto &device :deviceList) {
    auto listWidgetItem = new QListWidgetItem(materialRegular.visibilityOffIcon(), device->getDescription());
    listWidgetItem->setData(Qt::UserRole, device->getId());
    ui->listWidgetProximities->addItem(listWidgetItem);
  }
}
void MainWindow::onUpdateRelayListWidget(int deviceId, bool on) {

  for (int i = 0; i < ui->listWidgetRelays->count(); i++) {
    const auto listWidgetItem = ui->listWidgetRelays->item(i);
    QVariant id = listWidgetItem->data(Qt::UserRole);

    if(id == deviceId) {

      if(on) {
        listWidgetItem->setIcon(materialRegular.boltIcon(Qt::green));
      } else {
        listWidgetItem->setIcon(materialRegular.boltIcon(Qt::red));
      }
    }
  }
}
void MainWindow::onUpdateProximityListWidget(int deviceId, bool on) {
  for (int i = 0; i < ui->listWidgetProximities->count(); i++) {
    const auto listWidgetItem = ui->listWidgetProximities->item(i);
    QVariant id = listWidgetItem->data(Qt::UserRole);

    if(id == deviceId) {

      if(on) {
        listWidgetItem->setIcon(materialRegular.visibilityIcon());
      } else {
        listWidgetItem->setIcon(materialRegular.visibilityOffIcon());
      }
    }
  }
}
