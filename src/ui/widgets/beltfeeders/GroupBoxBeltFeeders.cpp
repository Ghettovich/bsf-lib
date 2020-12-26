#include "ui_groupboxbeltfeeders.h"
#include "GroupBoxBeltFeeders.h"
#include <relay.h>
#include <BsfWidgetEnum.h>

GroupBoxBeltFeeders::GroupBoxBeltFeeders(MqttClient *_m_client) :
    ui(new Ui::GroupBoxBeltFeeders), m_client(_m_client) {
  ui->setupUi(this);
  QVariant formId = WIDGET_TYPES::GROUPBOX_BELT_FEEDERS;
  this->setProperty("formId", formId);

  relayBeltForward = new Relay(0, IODevice::HIGH); // ON 2nd RELAY BLOCK, currently not present
  relayBeltReverse = new Relay(0, IODevice::HIGH); // ON 2nd RELAY BLOCK, currently not present

  relayFeeder1Foward = new Relay(34, IODevice::HIGH);
  relayFeeder1Reverse = new Relay(35, IODevice::HIGH);
  relayFeeder2Foward = new Relay(36, IODevice::HIGH);
  relayFeeder2Reverse = new Relay(37, IODevice::HIGH);

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

void GroupBoxBeltFeeders::onUpdateIODevices(const QVector<IODevice *> &iodeviceList) {
  for (auto iodevice : iodeviceList) {
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
  //m_client->publishToggleRelay(relayBeltForward);
}

void GroupBoxBeltFeeders::onClickPushButtonBeltReverse() {
  //m_client->publishToggleRelay(relayBeltReverse);
}

void GroupBoxBeltFeeders::onClickPushButtonFeeder1Forward() {
  m_client->publishToggleRelay(relayFeeder1Foward);
}

void GroupBoxBeltFeeders::onClickPushButtonFeeder1Reverse() {
  m_client->publishToggleRelay(relayFeeder1Reverse);
}

void GroupBoxBeltFeeders::onClickPushButtonFeeder2Forward() {
  m_client->publishToggleRelay(relayFeeder2Foward);
}

void GroupBoxBeltFeeders::onClickPushButtonFeeder2Reverse() {
  m_client->publishToggleRelay(relayFeeder2Reverse);
}
