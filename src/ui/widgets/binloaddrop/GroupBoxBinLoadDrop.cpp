#include "ui_groupboxbinloaddrop.h"
#include "GroupBoxBinLoadDrop.h"

#include <iodevice/relay.h>
#include <iodevice/detectionsensor.h>

#include <QSettings>

using namespace appservice;

GroupBoxBinLoadDrop::GroupBoxBinLoadDrop(std::shared_ptr<BrokerAppService> &_brokerAppService, QWidget *parent)
    :
    ui(new Ui::GroupBoxBinLoadDrop), brokerAppService(_brokerAppService), QWidget(parent) {
  ui->setupUi(this);

  connect(brokerAppService.get(), &appservice::BrokerAppService::updateDevicesWithState,
          this, &GroupBoxBinLoadDrop::onUpdateIODevices);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  relayBinLoad = std::make_unique<Relay>(settings->value("binload").toInt(), IODevice::HIGH); // Digital
  relayBinDrop = std::make_unique<Relay>(settings->value("bindrop").toInt(), IODevice::HIGH); // Digital

  settings->endGroup();

  settings->beginGroup("detectionsensor");
  proximityBinDrop =
      std::make_unique<DetectionSensor>(settings->value("bindrop").toInt(), IODevice::HIGH); // PULL UP (HIGH = OFF!)

  settings->endGroup();

  init();
}

GroupBoxBinLoadDrop::~GroupBoxBinLoadDrop() {
  delete ui;
}

void GroupBoxBinLoadDrop::init() {
  ui->labelProximityBinDropStatus->setText("");

  setProximityBinDropLabelStatus();
  setBinLoadButtonState();
  setBinDropButtonState();

  connect(ui->pushButtonBinLoadRelay, &QPushButton::clicked,
          this, &GroupBoxBinLoadDrop::onClickPushButtonBinLoad);
  connect(ui->pushButtonBinDropRelay, &QPushButton::clicked,
          this, &GroupBoxBinLoadDrop::onClickPushButtonBinDrop);
}

void GroupBoxBinLoadDrop::setProximityBinDropLabelStatus() {
  if (proximityBinDrop->isDeviceOn()) {
    ui->labelProximityBinDropStatus->setPixmap(materialRegular.visibilityIcon(Qt::lightGray).pixmap(48, 48));
  } else {
    ui->labelProximityBinDropStatus->setPixmap(materialRegular.visibilityOffIcon(Qt::darkGray).pixmap(48, 48));
  }
}

void GroupBoxBinLoadDrop::setBinLoadButtonState() {
  if (!relayBinLoad->isDeviceOn()) {
    ui->pushButtonBinLoadRelay->setIcon(materialRegular.boltIcon(Qt::green));
    ui->pushButtonBinLoadRelay->setText("LOAD ON");
  } else {
    ui->pushButtonBinLoadRelay->setIcon(materialRegular.boltIcon(Qt::red));
    ui->pushButtonBinLoadRelay->setText("LOAD OFF");
  }
}

void GroupBoxBinLoadDrop::setBinDropButtonState() {
  if (!relayBinDrop->isDeviceOn()) {
    ui->pushButtonBinDropRelay->setIcon(materialRegular.boltIcon(Qt::green));
    ui->pushButtonBinDropRelay->setText("DROP ON");
  } else {
    ui->pushButtonBinDropRelay->setIcon(materialRegular.boltIcon(Qt::red));
    ui->pushButtonBinDropRelay->setText("DROP OFF");
  }
}

void GroupBoxBinLoadDrop::onClickPushButtonBinLoad() {
  brokerAppService->toggleRelay(relayBinLoad->getId());
}

void GroupBoxBinLoadDrop::onClickPushButtonBinDrop() {
  brokerAppService->toggleRelay(relayBinDrop->getId());
}

void GroupBoxBinLoadDrop::onUpdateIODevices(const QVector<IODevice *> &devices) {
  for (auto iodevice : devices) {
    if (iodevice->getId() == proximityBinDrop->getId()) {
      onChangeProximity(iodevice);
    } else if (iodevice->getId() == relayBinLoad->getId()) {
      onToggledBinLoadRelay(iodevice);
    } else if (iodevice->getId() == relayBinDrop->getId()) {
      onToggledBinDropRelay(iodevice);
    }
  }
}

void GroupBoxBinLoadDrop::onChangeProximity(IODevice *detectionSensor) {
  proximityBinDrop->setDeviceState(detectionSensor->getDeviceState());
  setProximityBinDropLabelStatus();
  //emit proximityStateChange(proximityBinDrop);
}

void GroupBoxBinLoadDrop::onToggledBinLoadRelay(IODevice *relay) {
  relayBinLoad->setDeviceState(relay->getDeviceState());
  setBinLoadButtonState();
  //emit toggledRelay(relayBinLoad);
}

void GroupBoxBinLoadDrop::onToggledBinDropRelay(IODevice *relay) {
  relayBinDrop->setDeviceState(relay->getDeviceState());
  setBinDropButtonState();
  //emit toggledRelay(relayBinDrop);
}
