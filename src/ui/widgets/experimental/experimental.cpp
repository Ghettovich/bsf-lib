#include "ui_experimental.h"
#include "experimental.h"

#include <iodevice/iodevice.h>

#include <QSettings>

using namespace appservice;

Experimental::Experimental(std::shared_ptr<IODeviceAppService> &_deviceAppService, QWidget *parent) :
    ui(new Ui::Experimental), deviceAppService(_deviceAppService), QWidget(parent) {
  ui->setupUi(this);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  auto relayBinLiftDown = deviceAppService->findOne(settings->value("liftdown").toInt());

  ui->pushButtonLiftDown->setProperty("relay", relayBinLiftDown->getId());
  ui->pushButtonLiftDown->setText(relayBinLiftDown->getDescription());

  auto relayBinLiftUp = deviceAppService->findOne(settings->value("liftup").toInt());

  ui->pushButtonLiftUp->setProperty("relay", relayBinLiftUp->getId());
  ui->pushButtonLiftUp->setText(relayBinLiftUp->getDescription());

  settings->endGroup();

  settings->beginGroup("detectionsensor");

  auto proximityBinLoad = deviceAppService->findOne(settings->value("binload").toInt());
  ui->labelBinLoadDetected->setToolTip(proximityBinLoad->getDescription());
  ui->labelBinLoadDetected->setProperty("binload", proximityBinLoad->getId()); // PULL UP (HIGH = OFF!)

  settings->endGroup();

  connect(ui->pushButtonLiftDown, &RelayButton::toggleRelay,deviceAppService.get(), &IODeviceAppService::onToggleRelay);
  connect(ui->pushButtonLiftUp, &RelayButton::toggleRelay, deviceAppService.get(), &IODeviceAppService::onToggleRelay);
  connect(deviceAppService.get(), &IODeviceAppService::updateIODeviceState,this, &Experimental::onIODeviceStateChanged);
}
Experimental::~Experimental() {
  delete ui;
}
void Experimental::onIODeviceStateChanged(int deviceId, bool on) {

  if (ui->labelBinLoadDetected->property("binload").toInt() == deviceId) {
    ui->labelBinLoadDetected->updateProximityStatus(on);
  }
}
QList<QWidget *> Experimental::deviceWidgets() {
  return QList<QWidget *>()
      << ui->labelBinLoadDetected
      << ui->pushButtonLiftUp
      << ui->pushButtonLiftDown;
}
