#include "machine.service.h"

#include <QDebug>

service::MachineService::MachineService(QObject *parent) :
    QObject(parent) {
}

void service::MachineService::onIODeviceChange(int deviceId, bool status) {
  if (deviceId < 20) {
    proximityStatusChange(deviceId, status);
  } else if (deviceId < 50) {
    relayStatusChange(deviceId, status);
  }
}

void service::MachineService::proximityStatusChange(int deviceId, bool status) {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("detectionsensor");

  if (settings->value("bindrop").toInt() == deviceId) {
    emit proximityDropChanged(status);
  } else if (settings->value("binload").toInt() == deviceId) {
    emit proximityLoadChanged(status);
  } else {
    qWarning() << "Could not find proxmity to update";
  }

  settings->endGroup();
}
void service::MachineService::relayStatusChange(int deviceId, bool status) {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  if (settings->value("liftdown").toInt() == deviceId) {
    emit relayLiftDownChanged(status);
  } else if (settings->value("liftup").toInt() == deviceId) {
    emit relayLiftUpChanged(status);
  } else {
    qWarning() << "Could not find relay to update";
  }

  settings->endGroup();
}
