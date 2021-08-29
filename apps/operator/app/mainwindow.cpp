#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLayout>
#include <widgets/liftupdown/GroupBoxLiftUpDown.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>
#include <widgets/beltfeeders/GroupBoxBeltFeeders.h>
#include <widgets/recipeconfig/GroupBoxRecipeConfig.h>
#include <widgets/binrecipestatus/GroupBoxBinRecipeStatus.h>
#include <widgets/statusproximities/ProximityTreeWidget.h>
#include <widgets/statusrelays/RelayTreeWidget.h>

using namespace appservice;

MainWindow::MainWindow(std::shared_ptr<PrepareRecipeAppService> &_prepareRecipeAppService,
                       std::shared_ptr<MixRecipeAppService> &_mixRecipeAppService,
                       std::shared_ptr<BrokerAppService> &_brokerAppService,
                       QWidget *parent)
    :
    QMainWindow(parent),
    prepareRecipeAppService(_prepareRecipeAppService),
    mixRecipeAppService(_mixRecipeAppService),
    brokerAppService(_brokerAppService),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(brokerAppService.get(), &BrokerAppService::connectedToHost, [=]() {
    brokerAppService->onCreateDeviceStateSubscriptions();
  });
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::showSidebar() {
  createStateWidget();
  createRelayTreeView();
  createProximityTreeView();
}

void MainWindow::showStart() {
  createGroupBoxBinLift();
  createGroupBoxBinLoadDrop();
  createGroupBoxFeedersAndBelt();
  createGroupBoxRecipeConfiguration();
  createGroupBoxBinRecipeStatus();
}

void MainWindow::createRelayTreeView() {
  auto relayTreeWidget = new RelayTreeWidget(brokerAppService);
  ui->verticalLayoutSidePanel->addWidget(relayTreeWidget);
}

void MainWindow::createProximityTreeView() {
  auto proximityTreeWidget = new ProximityTreeWidget(brokerAppService);
  ui->verticalLayoutSidePanel->addWidget(proximityTreeWidget);
}

void MainWindow::createStateWidget() {
  auto stateWidget = new QWidget;
  auto layout = new QVBoxLayout(stateWidget);

  auto statusLabel = new QLabel("status: unknown");
  layout->addWidget(statusLabel);

  ui->verticalLayoutSidePanel->addWidget(stateWidget);
}

void MainWindow::createGroupBoxBinLift() {
  auto groupBoxLiftUpDown = new GroupBoxLiftUpDown(brokerAppService);
  ui->verticalLayoutTabLeft->addWidget(groupBoxLiftUpDown);
}

void MainWindow::createGroupBoxBinLoadDrop() {
  auto groupBoxBinLoadDrop = new GroupBoxBinLoadDrop(brokerAppService);
  ui->verticalLayoutTabLeft->addWidget(groupBoxBinLoadDrop);
}

void MainWindow::createGroupBoxFeedersAndBelt() {
  auto groupBoxBeltFeeders = new GroupBoxBeltFeeders(brokerAppService);
  ui->verticalLayoutTabLeft->addWidget(groupBoxBeltFeeders);
}

void MainWindow::createGroupBoxRecipeConfiguration() {
  auto groupBoxRecipeConfig = new GroupBoxRecipeConfig(brokerAppService, prepareRecipeAppService);
  ui->verticalLayoutTabLeft->addWidget(groupBoxRecipeConfig);
}
void MainWindow::createGroupBoxBinRecipeStatus() {
  auto groupBoxBinRecipeStatus = new GroupBoxBinRecipeStatus(prepareRecipeAppService);
  ui->verticalLayoutTabRight->addWidget(groupBoxBinRecipeStatus);
}
