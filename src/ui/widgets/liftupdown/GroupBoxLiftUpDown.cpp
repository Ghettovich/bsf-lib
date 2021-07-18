#include "ui_groupboxliftupdown.h"
#include "GroupBoxLiftUpDown.h"

#include <relay.h>
#include <detectionsensor.h>

#include <QSettings>

using namespace appservice;

GroupBoxLiftUpDown::GroupBoxLiftUpDown(std::shared_ptr<BrokerAppService> &_brokerAppService, QWidget *parent)
    :
    ui(new Ui::GroupBoxLiftUpDown), brokerAppService(_brokerAppService), QWidget(parent) {
  ui->setupUi(this);

  connect(brokerAppService.get(), &BrokerAppService::updateDevicesWithState,
          this, &GroupBoxLiftUpDown::onUpdateIODevices);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  relayBinLiftDown = std::make_unique<Relay>(settings->value("liftdown").toInt(), IODevice::HIGH); // Digital
  relayBinLiftUp = std::make_unique<Relay>(settings->value("liftup").toInt(), IODevice::HIGH); // Digital

  settings->endGroup();

  settings->beginGroup("detectionsensor");
  proximityBinLoad = std::make_unique<DetectionSensor>(settings->value("binload").toInt(), IODevice::HIGH); // PULL UP (HIGH = OFF!)

  settings->endGroup();

  init();
}

GroupBoxLiftUpDown::~GroupBoxLiftUpDown() {
  delete ui;
}

void GroupBoxLiftUpDown::init() {
  ui->labelProximityBinLoadStatus->setText("");
  setProximityBinLoadStatusLabel();
  setLiftDownButtonState();
  setLiftUpButtonState();

  connect(ui->pushButtonLiftDown, &QPushButton::clicked,
          this, &GroupBoxLiftUpDown::onClickPushButtonLiftDown);

  connect(ui->pushButtonLiftUp, &QPushButton::clicked,
          this, &GroupBoxLiftUpDown::onClickPushButtonLiftUp);
}

void GroupBoxLiftUpDown::onClickPushButtonLiftDown() {
  brokerAppService->toggleRelay(relayBinLiftDown->getId());
}

void GroupBoxLiftUpDown::onClickPushButtonLiftUp() {
  brokerAppService->toggleRelay(relayBinLiftUp->getId());
}

void GroupBoxLiftUpDown::setProximityBinLoadStatusLabel() {
  qDebug() << "updating label ... ";

  if (proximityBinLoad->isDeviceOn()) {
    ui->labelProximityBinLoadStatus->setPixmap(materialRegular.visibilityIcon(Qt::lightGray).pixmap(48, 48));
  } else {
    ui->labelProximityBinLoadStatus->setPixmap(materialRegular.visibilityOffIcon(Qt::darkGray).pixmap(48, 48));
  }
}

void GroupBoxLiftUpDown::setLiftUpButtonState() {
  if (!relayBinLiftUp->isDeviceOn()) {
    ui->pushButtonLiftUp->setText("UP ON");
    ui->pushButtonLiftUp->setIcon(materialRegular.boltIcon(Qt::green));
  } else {
    ui->pushButtonLiftUp->setText("UP OFF");
    ui->pushButtonLiftUp->setIcon(materialRegular.boltIcon(Qt::red));
  }
}

void GroupBoxLiftUpDown::setLiftDownButtonState() {
  if (!relayBinLiftDown->isDeviceOn()) {
    ui->pushButtonLiftDown->setText("DOWN ON");
    ui->pushButtonLiftDown->setIcon(materialRegular.boltIcon(Qt::green));
  } else {
    ui->pushButtonLiftDown->setText("DOWN OFF");
    ui->pushButtonLiftDown->setIcon(materialRegular.boltIcon(Qt::red));
  }
}

void GroupBoxLiftUpDown::onUpdateIODevices(const QVector<IODevice *> &devices) {
  for (auto iodevice : devices) {
    if (iodevice->getId() == proximityBinLoad->getId()) {
      onChangeProximity(iodevice);
    } else if (iodevice->getId() == relayBinLiftUp->getId()) {
      onToggledLiftUpRelay(iodevice);
    } else if (iodevice->getId() == relayBinLiftDown->getId()) {
      onToggledLiftDownRelay(iodevice);
    }
  }
}

void GroupBoxLiftUpDown::onChangeProximity(IODevice *detectionSensor) {
  proximityBinLoad->setDeviceState(detectionSensor->getDeviceState());
  setProximityBinLoadStatusLabel();
  //emit proximityStateChange(proximityBinLoad);
}

void GroupBoxLiftUpDown::onToggledLiftUpRelay(IODevice *relay) {
  relayBinLiftUp->setDeviceState(relay->getDeviceState());
  setLiftUpButtonState();
  //emit toggledRelay(relayBinLiftUp);
}

void GroupBoxLiftUpDown::onToggledLiftDownRelay(IODevice *relay) {
  relayBinLiftDown->setDeviceState(relay->getDeviceState());
  setLiftDownButtonState();
  //emit toggledRelay(relayBinLiftDown);
}

