#include "ui_groupboxliftupdown.h"
#include "GroupBoxLiftUpDown.h"
#include <BsfWidgetEnum.h>

GroupBoxLiftUpDown::GroupBoxLiftUpDown(MqttClient *_m_client)
    :
    ui(new Ui::GroupBoxLiftUpDown), m_client(_m_client) {
  ui->setupUi(this);
  QVariant formId = WIDGET_TYPES::GROUPBOX_LIFT_UP_DOWN;
  this->setProperty("formId", formId);

  relayBinLiftDown = new Relay(31, IODevice::HIGH); // Digital
  relayBinLiftUp = new Relay(30, IODevice::HIGH); // Digital
  proximityBinLoad = new DetectionSensor(11, IODevice::HIGH); // PULL UP (HIGH = OFF!)

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
  m_client->publishToggleRelay(relayBinLiftDown);
}

void GroupBoxLiftUpDown::onClickPushButtonLiftUp() {
  m_client->publishToggleRelay(relayBinLiftUp);
}

void GroupBoxLiftUpDown::setProximityBinLoadStatusLabel() {
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

void GroupBoxLiftUpDown::onUpdateIODevices(const QVector<IODevice *> &iodeviceList) {
  for (auto iodevice : iodeviceList) {
    if (iodevice->getId() == proximityBinLoad->getId()) {
      proximityBinLoad->setDeviceState(iodevice->getDeviceState());
    } else if (iodevice->getId() == relayBinLiftUp->getId()) {
      relayBinLiftUp->setDeviceState(iodevice->getDeviceState());
    } else if (iodevice->getId() == relayBinLiftDown->getId()) {
      relayBinLiftDown->setDeviceState(iodevice->getDeviceState());
    }
  }

  if (!iodeviceList.empty()) {
    setLiftDownButtonState();
    setLiftUpButtonState();
    setProximityBinLoadStatusLabel();
  }
}

