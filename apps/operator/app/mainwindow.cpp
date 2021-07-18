#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <widgets/liftupdown/GroupBoxLiftUpDown.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>
#include <widgets/beltfeeders/GroupBoxBeltFeeders.h>
#include <widgets/recipeconfig/GroupBoxRecipeConfig.h>
#include <widgets/binrecipestatus/GroupBoxBinRecipeStatus.h>
#include <widgets/statusproximities/ProximityTreeWidget.h>
#include <widgets/statusrelays/RelayTreeWidget.h>

//#include <ui/mqttclient/OperatorMqttClient.h>

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

  connect(brokerAppService.get(), &BrokerAppService::connectedToHost, [=](){
    brokerAppService->createDeviceStateSubscriptions();
  });

  //createMqttClientWindow();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::showSidebar() {
  createRelayTreeView();
  createProximityTreeView();
}

void MainWindow::showStart() {
//  createClientDescriptions();
  createGroupBoxBinLift();
  createGroupBoxBinLoadDrop();
  createGroupBoxFeedersAndBelt();
//  createGroupBoxRecipeConfiguration();
//  createGroupBoxBinRecipeStatus();
}

void MainWindow::createRelayTreeView() {
  auto relayTreeWidget = new RelayTreeWidget(brokerAppService);
  ui->verticalLayoutSidePanel->addWidget(relayTreeWidget);
}

void MainWindow::createProximityTreeView() {
  auto proximityTreeWidget = new ProximityTreeWidget(brokerAppService);
  ui->verticalLayoutSidePanel->addWidget(proximityTreeWidget);
}

void MainWindow::createArduinoTreeView() {
//  ArduinoRepository arduinoRepository;
//  QList<QTreeWidgetItem *> arduinoTreeWidgets = arduinoRepository.getArduinoTreeWidgets();
//
//  QStringList headers;
//  headers.append("ID");
//  headers.append("Type");
//  headers.append("Status");
//  headers.append("Arduino");

//    auto arduinoTreeWidget = new TreeWidgetDeviceStatus(headers, arduinoTreeWidgets);
//    ui->verticalLayoutSidePanel->addWidget(arduinoTreeWidget);
}

void MainWindow::createClientsTreeView() {

}

void MainWindow::createClientDescriptions() {
//    ui->labelClientInfoTitle->setText("Operator");
//    ui->labelClientInfo->setText("IP: 192.168.178.X \nGateWay: 192.168.178.X");
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
  auto groupBoxRecipeConfig = new GroupBoxRecipeConfig(m_client);
  ui->verticalLayoutTabLeft->addWidget(groupBoxRecipeConfig);
}

void MainWindow::createGroupBoxBinRecipeStatus() {
//  groupBoxBinRecipeStatus = new GroupBoxBinRecipeStatus(m_client);
//  ui->verticalLayoutTabRight->addWidget(groupBoxBinRecipeStatus);
}

void MainWindow::createMqttClientWindow() {
//  auto operatorMqttClient = new OperatorMqttClient(ui->tab_2, Qt::Widget);
//  operatorMqttClient->showFullScreen();
}

QTabWidget *MainWindow::getApplicationTabWidget() {
  return ui->tabWidget;
}

void MainWindow::onCreateMqttClientSubscriptions() {
//  quint8 QoS = 1;
//  const QString topicProximityLift("/proximity/lift");
//  const QString topicRelayStates("/relay/states");

//  //GroupBox Lift Up Down
//  m_client->addIODeviceSubscription(topicProximityLift, QoS, groupBoxLiftUpDown);
//  m_client->addIODeviceSubscription(topicRelayStates, QoS, groupBoxLiftUpDown);
//
//  //GroupBox Bin Load Drop
//  m_client->addIODeviceSubscription(topicProximityLift, QoS, groupBoxBinLoadDrop);
//  m_client->addIODeviceSubscription(topicRelayStates, QoS, groupBoxBinLoadDrop);
//
//  //GroupBox Belt And Feeders
//  m_client->addIODeviceSubscription(topicRelayStates, QoS, groupBoxBeltFeeders);
//
//  //m_client->addIODeviceSubscription(topicRelayStates, QoS, relayTreeWidget);
//  m_client->addIODeviceSubscription(topicProximityLift, QoS, proximityTreeWidget);
//
//  //GroupBox Recipe Status Bin & Scale 1
//  m_client->addRecipeDataSubscription(QoS, groupBoxBinRecipeStatus);
}
