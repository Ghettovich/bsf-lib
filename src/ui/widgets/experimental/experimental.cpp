#include "ui_experimental.h"
#include "experimental.h"

#include <iodevice/iodevice.h>

#include <QSettings>

using namespace appservice;

Experimental::Experimental(std::shared_ptr<IODeviceAppService> &_deviceAppService,
                           std::shared_ptr<appservice::StateMachineAppService> &_statemachineAppService,
                           QWidget *parent) :
    ui(new Ui::Experimental),
    deviceAppService(_deviceAppService),
    statemachineAppService(_statemachineAppService),
    QWidget(parent) {
  ui->setupUi(this);

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  auto relayBinLiftDown = deviceAppService->findOne(settings->value("liftdown").toInt());

  ui->pushButtonLiftDown->setProperty("deviceId", relayBinLiftDown->getId());
  ui->pushButtonLiftDown->setProperty("sensor", "relay");
  ui->pushButtonLiftDown->setText(relayBinLiftDown->getDescription());

  auto relayBinLiftUp = deviceAppService->findOne(settings->value("liftup").toInt());

  ui->pushButtonLiftUp->setProperty("deviceId", relayBinLiftUp->getId());
  ui->pushButtonLiftUp->setProperty("sensor", "relay");
  ui->pushButtonLiftUp->setText(relayBinLiftUp->getDescription());

  settings->endGroup();

  settings->beginGroup("detectionsensor");

  auto proximityBinLoad = deviceAppService->findOne(settings->value("binload").toInt());
  ui->labelBinLoadDetected->setToolTip(proximityBinLoad->getDescription());
  ui->labelBinLoadDetected->setProperty("sensor", "proximity");
  ui->labelBinLoadDetected->setProperty("deviceId", proximityBinLoad->getId()); // PULL UP (HIGH = OFF!)

  settings->endGroup();

  QObject::connect(ui->pushButtonEmptyTable, &QPushButton::clicked, [=](){
    statemachineAppService->sendLiftToBottom();
  });
}

Experimental::~Experimental() {
  delete ui;
}

QList<QWidget *> Experimental::deviceWidgets() {
  return QList<QWidget *>()
      << ui->labelBinLoadDetected
      << ui->pushButtonLiftUp
      << ui->pushButtonLiftDown;
}
