#include "MainWindow.h"
#include <recipe.h>
#include <arduinorepo.h>
#include <iodevicerepo.h>
#include <widgets/statusproximities/ProximityTreeWidget.h>
#include <widgets/liftupdown/GroupBoxLiftUpDown.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>
#include <widgets/beltfeeders/GroupBoxBeltFeeders.h>
#include <widgets/recipeconfig/GroupBoxRecipeConfig.h>
#include <widgets/binrecipestatus/GroupBoxBinRecipeStatus.h>
#include <ui/mqttclient/OperatorMqttClient.h>
#include <widgets/statusrelays/RelayTreeWidget.h>

MainWindow::MainWindow(QWidget *parent)
    :
    QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_client = new MqttClient(this);

  connect(m_client, &MqttClient::brokerConnected,
          this, &MainWindow::onCreateMqttClientSubscriptions);

  m_client->connectToHost();

  createRelayTreeView();
  createProximityTreeView();
  createArduinoTreeView();
  createClientDescriptions();
  createGroupBoxBinLift();
  createGroupBoxBinLoadDrop();
  createGroupBoxFeedersAndBelt();
  createGroupBoxRecipeConfiguration();
  createGroupBoxBinRecipeStatus();

  //createMqttClientWindow();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::createRelayTreeView() {
  QStringList headers;
  headers.append("ID");
  headers.append("Type");
  headers.append("Status");
  headers.append("Relay");

  IODeviceRepository ioDeviceRepository;
  QList<QTreeWidgetItem *> relayTreeWidgetList = ioDeviceRepository.getIODeviceTreeWidgets(IODeviceType::RELAY);

  relayTreeWidget = new RelayTreeWidget(headers, relayTreeWidgetList);
  ui->verticalLayoutSidePanel->addWidget(relayTreeWidget);
}

void MainWindow::createProximityTreeView() {
  IODeviceRepository ioDeviceRepository;
  QList<QTreeWidgetItem *>
      proximityWidgetList = ioDeviceRepository.getIODeviceTreeWidgets(IODeviceType::DETECTIONSENSOR);

  QStringList headers;
  headers.append("ID");
  headers.append("Type");
  headers.append("Status");
  headers.append("Proximity");

  proximityTreeWidget = new ProximityTreeWidget(headers, proximityWidgetList);
  ui->verticalLayoutSidePanel->addWidget(proximityTreeWidget);
}

void MainWindow::createArduinoTreeView() {
  ArduinoRepository arduinoRepository;
  QList<QTreeWidgetItem *> arduinoTreeWidgets = arduinoRepository.getArduinoTreeWidgets();

  QStringList headers;
  headers.append("ID");
  headers.append("Type");
  headers.append("Status");
  headers.append("Arduino");

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
  groupBoxLiftUpDown = new GroupBoxLiftUpDown(m_client);
  ui->verticalLayoutTabLeft->addWidget(groupBoxLiftUpDown);
}

void MainWindow::createGroupBoxBinLoadDrop() {
  groupBoxBinLoadDrop = new GroupBoxBinLoadDrop(m_client);
  ui->verticalLayoutTabLeft->addWidget(groupBoxBinLoadDrop);
}

void MainWindow::createGroupBoxFeedersAndBelt() {
  groupBoxBeltFeeders = new GroupBoxBeltFeeders(m_client);
  ui->verticalLayoutTabLeft->addWidget(groupBoxBeltFeeders);
}

void MainWindow::createGroupBoxRecipeConfiguration() {
  groupBoxRecipeConfig = new GroupBoxRecipeConfig(m_client);
  ui->verticalLayoutTabLeft->addWidget(groupBoxRecipeConfig);
}

void MainWindow::createGroupBoxBinRecipeStatus() {
  groupBoxBinRecipeStatus = new GroupBoxBinRecipeStatus(m_client);
  ui->verticalLayoutTabRight->addWidget(groupBoxBinRecipeStatus);
}

void MainWindow::createMqttClientWindow() {
  auto operatorMqttClient = new OperatorMqttClient(ui->tab_2, Qt::Widget);
  operatorMqttClient->showFullScreen();
}

void MainWindow::onCreateMqttClientSubscriptions() {
  quint8 QoS = 1;
  const QString topicProximityLift("/proximity/lift");
  const QString topicRelayStates("/relay/states");

  //GroupBox Lift Up Down
  m_client->addIODeviceSubscription(topicProximityLift, QoS, groupBoxLiftUpDown);
  m_client->addIODeviceSubscription(topicRelayStates, QoS, groupBoxLiftUpDown);

  //GroupBox Bin Load Drop
  m_client->addIODeviceSubscription(topicProximityLift, QoS, groupBoxBinLoadDrop);
  m_client->addIODeviceSubscription(topicRelayStates, QoS, groupBoxBinLoadDrop);

  //GroupBox Belt And Feeders
  m_client->addIODeviceSubscription(topicRelayStates, QoS, groupBoxBeltFeeders);

  m_client->addIODeviceSubscription(topicRelayStates, QoS, relayTreeWidget);
  m_client->addIODeviceSubscription(topicProximityLift, QoS, proximityTreeWidget);

  //GroupBox Recipe Status Bin & Scale 1
  m_client->addRecipeDataSubscription(QoS, groupBoxBinRecipeStatus);
}
