#include "stateservice.h"

#include <memory>

#include <QMap>
#include <iodevice/relay.h>
#include <iodevice/weightcensor.h>

using namespace service;

StateService::StateService(std::shared_ptr<service::BrokerService> &_brokerService,
                           std::shared_ptr<IODeviceService> &_deviceService,
                           QObject *parent) :
    QObject(parent), brokerService(_brokerService), deviceService(_deviceService) {

  for (const auto &dev : deviceService->findAllDevices()) {
    deviceStateMap.insert(dev->getId(), dev->clone());
  }

  connect(brokerService.get(), &BrokerService::newMessageForTopic,
          this, &StateService::onNewIODeviceStates);

  connect(this, &StateService::updateIODeviceState,
          deviceService.get(), &IODeviceService::onUpdateIODeviceState);

  connect(this, &StateService::updateScaleDevice,
          deviceService.get(), &IODeviceService::onUpdateScaleDevice);
}

void StateService::createDeviceStateSubscriptions() {
  brokerService->addSubscription(relayStatesTopic);
  brokerService->addSubscription(proximityLiftTopic);
  brokerService->addSubscription(scaleDataTopic);
}

void StateService::parseRelayStates(const QByteArray &message) {
  parseIODevices(message);
}

void StateService::parseProximityStates(const QByteArray &message) {
  parseIODevices(message);
}

void StateService::parseIODevices(const QByteArray &payload) {
  QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));

  if (validateJsonDocument(jsonDocument)) {
    QJsonArray ioDeviceArray;

    if (jsonDocument["proximities"].isArray()) {
      ioDeviceArray = jsonDocument["proximities"].toArray();
    } else if (jsonDocument["relays"].isArray()) {
      ioDeviceArray = jsonDocument["relays"].toArray();
    }

    updateIODevices(ioDeviceArray);
  }
}

bool StateService::validateJsonDocument(QJsonDocument &jsonDocument) {
  auto parseError = new QJsonParseError;
  if (jsonDocument.isNull()) {
    QString error = QString("Failed to create JSON doc.\nError =%1").arg(parseError->errorString());
    qDebug() << error;
    return false;
  }
  if (!jsonDocument.isObject()) {
    QString error = QString("JSON is not an object.\nError = %1").arg(parseError->errorString());
    qDebug() << error;
    return false;
  }

  delete parseError;
  return true;
}

void StateService::updateScale(const QByteArray &message) {
  QJsonDocument jsonDocument(QJsonDocument::fromJson(message));

  if (validateJsonDocument(jsonDocument)) {
    int scaleId = jsonDocument["scaleId"].toInt();
    double weight = jsonDocument["weight"].toDouble();

    emit updateScaleDevice(scaleId, weight);
    qDebug() << message;
  }
}

void StateService::updateIODevices(const QJsonArray &jsonArray) {

  for (const auto &i : jsonArray) {
    QJsonObject ioDeviceObject = i.toObject();

    if (ioDeviceObject.contains("id")) {
      IODevice::IO_DEVICE_HIGH_LOW state = ioDeviceObject["low"].toInt() == 1 ? IODevice::LOW : IODevice::HIGH;

      if(deviceStateMap.value(ioDeviceObject["id"].toInt())->isStateChanged(state)) {
        deviceStateMap.value(ioDeviceObject["id"].toInt())->setDeviceState(state);

        emit updateIODeviceState(deviceStateMap.value(ioDeviceObject["id"].toInt())->getId(), state);
        qDebug() << "Updated device in device list";
      }
    }
  }
}

void StateService::onNewIODeviceStates(const QByteArray &message, const QString &topic) {
  if (topic.compare(relayStatesTopic) == 0) {
    parseRelayStates(message);
  } else if (topic.compare(proximityLiftTopic) == 0) {
    parseProximityStates(message);
  } else if (topic.compare(scaleDataTopic) == 0) {
    updateScale(message);
  }
}
