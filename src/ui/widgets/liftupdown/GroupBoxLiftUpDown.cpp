#include "ui_groupboxliftupdown.h"
#include "GroupBoxLiftUpDown.h"
#include <BsfWidgetEnum.h>

GroupBoxLiftUpDown::GroupBoxLiftUpDown(MqttClient *_m_client)
    :
    ui(new Ui::GroupBoxLiftUpDown), m_client(_m_client) {
  ui->setupUi(this);
  QVariant formId = WIDGET_TYPES::GROUPBOX_LIFT_UP_DOWN;
  this->setProperty("formId", formId);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  relayBinLiftDown = new Relay(settings->value("liftdown").toInt(), IODevice::HIGH); // Digital
  relayBinLiftUp = new Relay(settings->value("liftup").toInt(), IODevice::HIGH); // Digital

  settings->beginGroup("detection_sensor");
  proximityBinLoad = new DetectionSensor(settings->value("binload").toInt(), IODevice::HIGH); // PULL UP (HIGH = OFF!)

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
  emit proximityStateChange(proximityBinLoad);
}

void GroupBoxLiftUpDown::onToggledLiftUpRelay(IODevice *relay) {
  relayBinLiftUp->setDeviceState(relay->getDeviceState());
  setLiftUpButtonState();
  emit toggledRelay(relayBinLiftUp);
}

void GroupBoxLiftUpDown::onToggledLiftDownRelay(IODevice *relay) {
  relayBinLiftDown->setDeviceState(relay->getDeviceState());
  setLiftDownButtonState();
  emit toggledRelay(relayBinLiftDown);
}

