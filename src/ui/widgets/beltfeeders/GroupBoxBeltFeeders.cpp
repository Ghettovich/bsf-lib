#include "ui_groupboxbeltfeeders.h"
#include "GroupBoxBeltFeeders.h"
#include <iodevice/relay.h>

using namespace appservice;

GroupBoxBeltFeeders::GroupBoxBeltFeeders(std::shared_ptr<BrokerAppService> &_brokerAppService,
                                         QWidget *parent)
    :
    ui(new Ui::GroupBoxBeltFeeders), brokerAppService(_brokerAppService), QWidget(parent) {
  ui->setupUi(this);

  connect(brokerAppService.get(), &appservice::BrokerAppService::updateDevicesWithState,
          this, &GroupBoxBeltFeeders::onUpdateIODevices);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  relayBeltForward = std::make_unique<Relay>(0, IODevice::HIGH); // ON 2nd RELAY BLOCK, currently not present
  relayBeltReverse = std::make_unique<Relay>(0, IODevice::HIGH); // ON 2nd RELAY BLOCK, currently not present

  relayFeeder1Foward = std::make_unique<Relay>(settings->value("feeder1forward").toInt(), IODevice::HIGH);
  relayFeeder1Reverse = std::make_unique<Relay>(settings->value("feeder1reverse").toInt(), IODevice::HIGH);
  relayFeeder2Foward = std::make_unique<Relay>(settings->value("feeder2forward").toInt(), IODevice::HIGH);
  relayFeeder2Reverse = std::make_unique<Relay>(settings->value("feeder2reverse").toInt(), IODevice::HIGH);

  settings->endGroup();

  init();
}

void GroupBoxBeltFeeders::init() {
  ui->labelRelayBeltStatus->setText("No recipe known");
  ui->labelRelayFeeder1Status->setText("Rem. materials%");
  ui->labelRelayFeeder2Status->setText("Rem. materials%");

  setBeltForwardButtonState();
  setBeltReverseButtonState();
  setFeeder1ForwardButtonState();
  setFeeder1ReverseButtonState();
  setFeeder2ForwardButtonState();
  setFeeder2ReverseButtonState();

  connect(ui->pushButtonBeltForward, &QPushButton::clicked,
          this, &GroupBoxBeltFeeders::onClickPushButtonBeltForward);

  connect(ui->pushButtonBeltReverse, &QPushButton::clicked,
          this, &GroupBoxBeltFeeders::onClickPushButtonBeltReverse);

  connect(ui->pushButtonFeeder1Forward, &QPushButton::clicked,
          this, &GroupBoxBeltFeeders::onClickPushButtonFeeder1Forward);

  connect(ui->pushButtonFeeder1Reverse, &QPushButton::clicked,
          this, &GroupBoxBeltFeeders::onClickPushButtonFeeder1Reverse);

  connect(ui->pushButtonFeeder2Forward, &QPushButton::clicked,
          this, &GroupBoxBeltFeeders::onClickPushButtonFeeder2Forward);

  connect(ui->pushButtonFeeder2Reverse, &QPushButton::clicked,
          this, &GroupBoxBeltFeeders::onClickPushButtonFeeder2Reverse);
}

void GroupBoxBeltFeeders::onUpdateIODevices(const QVector<IODevice *> &devices) {
  for (auto iodevice : devices) {
    if (iodevice->getId() == relayBeltForward->getId()) {
      relayBeltForward->setDeviceState(iodevice->getDeviceState());
      setBeltForwardButtonState();
    } else if (iodevice->getId() == relayBeltReverse->getId()) {
      relayBeltReverse->setDeviceState(iodevice->getDeviceState());
      setBeltReverseButtonState();
    } else if (iodevice->getId() == relayFeeder1Foward->getId()) {
      relayFeeder1Foward->setDeviceState(iodevice->getDeviceState());
      setFeeder1ForwardButtonState();
    } else if (iodevice->getId() == relayFeeder1Reverse->getId()) {
      relayFeeder1Reverse->setDeviceState(iodevice->getDeviceState());
      setFeeder1ReverseButtonState();
    } else if (iodevice->getId() == relayFeeder2Foward->getId()) {
      relayFeeder2Foward->setDeviceState(iodevice->getDeviceState());
      setFeeder2ForwardButtonState();
    } else if (iodevice->getId() == relayFeeder2Reverse->getId()) {
      relayFeeder2Reverse->setDeviceState(iodevice->getDeviceState());
      setFeeder2ReverseButtonState();
    }
  }
}

void GroupBoxBeltFeeders::setBeltForwardButtonState() {
  ui->pushButtonBeltForward->setDisabled(true);
}

void GroupBoxBeltFeeders::setBeltReverseButtonState() {
  ui->pushButtonBeltReverse->setDisabled(true);
}

void GroupBoxBeltFeeders::setFeeder1ForwardButtonState() {
  if (!relayFeeder1Foward->isDeviceOn()) {
    ui->pushButtonFeeder1Forward->setIcon(materialRegular.boltIcon(Qt::green));
    ui->pushButtonFeeder1Forward->setText("FORWARD ON");
  } else {
    ui->pushButtonFeeder1Forward->setIcon(materialRegular.boltIcon(Qt::red));
    ui->pushButtonFeeder1Forward->setText("FORWARD OFF");
  }
}

void GroupBoxBeltFeeders::setFeeder1ReverseButtonState() {
  if (!relayFeeder1Reverse->isDeviceOn()) {
    ui->pushButtonFeeder1Reverse->setIcon(materialRegular.boltIcon(Qt::green));
    ui->pushButtonFeeder1Reverse->setText("REVERSE ON");
  } else {
    ui->pushButtonFeeder1Reverse->setIcon(materialRegular.boltIcon(Qt::red));
    ui->pushButtonFeeder1Reverse->setText("REVERSE OFF");
  }
}

void GroupBoxBeltFeeders::setFeeder2ForwardButtonState() {
  if (!relayFeeder2Foward->isDeviceOn()) {
    ui->pushButtonFeeder2Forward->setIcon(materialRegular.boltIcon(Qt::green));
    ui->pushButtonFeeder2Forward->setText("FORWARD ON");
  } else {
    ui->pushButtonFeeder2Forward->setIcon(materialRegular.boltIcon(Qt::red));
    ui->pushButtonFeeder2Forward->setText("FORWARD OFF");
  }
}

void GroupBoxBeltFeeders::setFeeder2ReverseButtonState() {
  if (!relayFeeder2Reverse->isDeviceOn()) {
    ui->pushButtonFeeder2Reverse->setIcon(materialRegular.boltIcon(Qt::green));
    ui->pushButtonFeeder2Reverse->setText("REVERSE ON");
  } else {
    ui->pushButtonFeeder2Reverse->setIcon(materialRegular.boltIcon(Qt::red));
    ui->pushButtonFeeder2Reverse->setText("REVERSE OFF");
  }
}

void GroupBoxBeltFeeders::onClickPushButtonBeltForward() {
  brokerAppService->toggleRelay(relayBeltForward->getId());
}

void GroupBoxBeltFeeders::onClickPushButtonBeltReverse() {
  brokerAppService->toggleRelay(relayBeltReverse->getId());
}

void GroupBoxBeltFeeders::onClickPushButtonFeeder1Forward() {
  brokerAppService->toggleRelay(relayFeeder1Foward->getId());
}

void GroupBoxBeltFeeders::onClickPushButtonFeeder1Reverse() {
  brokerAppService->toggleRelay(relayFeeder1Reverse->getId());
}

void GroupBoxBeltFeeders::onClickPushButtonFeeder2Forward() {
  brokerAppService->toggleRelay(relayFeeder2Foward->getId());
}

void GroupBoxBeltFeeders::onClickPushButtonFeeder2Reverse() {
  brokerAppService->toggleRelay(relayFeeder2Reverse->getId());
}
