#include "ui_groupboxbinloaddrop.h"
#include "GroupBoxBinLoadDrop.h"
#include <BsfWidgetEnum.h>

GroupBoxBinLoadDrop::GroupBoxBinLoadDrop(MqttClient *_m_client)
    :
    ui(new Ui::GroupBoxBinLoadDrop), m_client(_m_client) {
  ui->setupUi(this);
  QVariant formId = WIDGET_TYPES::GROUPBOX_BIN_LOAD_DROP;
  this->setProperty("formId", formId);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  relayBinLoad = new Relay(settings->value("binload").toInt(), IODevice::HIGH); // Digital
  relayBinDrop = new Relay(settings->value("bindrop").toInt(), IODevice::HIGH); // Digital

  settings->beginGroup("detection_sensor");
  proximityBinDrop = new DetectionSensor(settings->value("bindrop").toInt(), IODevice::HIGH); // PULL UP (HIGH = OFF!)

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
  m_client->publishToggleRelay(relayBinLoad);
}

void GroupBoxBinLoadDrop::onClickPushButtonBinDrop() {
  m_client->publishToggleRelay(relayBinDrop);
}

void GroupBoxBinLoadDrop::onUpdateIODevices(const QVector<IODevice *> &iodeviceList) {
  for (auto iodevice : iodeviceList) {
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
  emit proximityStateChange(proximityBinDrop);
}

void GroupBoxBinLoadDrop::onToggledBinLoadRelay(IODevice *relay) {
  relayBinLoad->setDeviceState(relay->getDeviceState());
  setBinLoadButtonState();
  emit toggledRelay(relayBinLoad);
}

void GroupBoxBinLoadDrop::onToggledBinDropRelay(IODevice *relay) {
  relayBinDrop->setDeviceState(relay->getDeviceState());
  setBinDropButtonState();
  emit toggledRelay(relayBinDrop);
}
