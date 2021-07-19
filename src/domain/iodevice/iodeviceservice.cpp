#include "iodeviceservice.h"

#include "iodevice.h"
#include "detectionsensor.h"
#include "relay.h"
#include "weightcensor.h"

using namespace service;

IODeviceService::IODeviceService(std::shared_ptr<DatabaseService> _databaseService,
                                 std::shared_ptr<service::BrokerService> &_brokerService,
                                 QObject *parent) :
    QObject(parent),
    deviceRepository(std::make_unique<IODeviceRepository>(_databaseService, this)),
    brokerService(_brokerService) {

  connect(brokerService.get(), &BrokerService::newMessageForTopic,
          this, &IODeviceService::onNewIODeviceStates);
}
QVector<IODevice *> IODeviceService::getIODevices(IODeviceType::IO_DEVICE_TYPE ioDeviceType) {
  return deviceRepository->getIODeviceList(ioDeviceType);
}
void IODeviceService::createDeviceStateSubscriptions() {
  brokerService->addSubscription(relayStatesTopic);
  brokerService->addSubscription(proximityLiftTopic);
  brokerService->addSubscription(recipeDataTopic);
}
void IODeviceService::onNewIODeviceStates(const QByteArray &message, const QString &topic) {
  if (topic.compare(relayStatesTopic) == 0) {
    parseRelayStates(message);
  } else if (topic.compare(proximityLiftTopic) == 0) {
    parseProximityStates(message);
  } else if (topic.compare(recipeDataTopic) == 0) {
    parseRecipeData(message);
  }
}
void IODeviceService::parseRelayStates(const QByteArray &message) {
  QVector<IODevice *> devices;

  devices = parseIODevices(message);

  emit updateRelayDevices(devices);
}
void IODeviceService::parseProximityStates(const QByteArray &message) {
  QVector<IODevice *> devices;

  devices = parseIODevices(message);

  emit updateProximityDevices(devices);
}
void IODeviceService::parseRecipeData(const QByteArray &message) {
  QJsonDocument jsonDocument(QJsonDocument::fromJson(message));

  if (validateJsonDocument(jsonDocument)) {
    IODevice::IO_DEVICE_HIGH_LOW scaleState;
    scaleState = jsonDocument["low"].toInt() == 0 ? IODevice::LOW : IODevice::HIGH;

    auto weightSensor = new WeightSensor(jsonDocument["did"].toInt(),
                                         jsonDocument["rid"].toInt(),
                                         jsonDocument["cid"].toInt(),
                                         jsonDocument["weight"].toInt(),
                                         scaleState);

    emit updateScale(weightSensor);
  }
}
QVector<IODevice *> IODeviceService::parseIODevices(const QByteArray &payload) {
  QVector<IODevice *> iodevices;
  QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));

  if (validateJsonDocument(jsonDocument)) {
    QJsonArray ioDeviceArray;

    if (jsonDocument["proximities"].isArray()) {
      ioDeviceArray = jsonDocument["proximities"].toArray();
      iodevices = addProximitiesToArray(ioDeviceArray);
    } else if (jsonDocument["relays"].isArray()) {
      ioDeviceArray = jsonDocument["relays"].toArray();
      iodevices = addRelaysToArray(ioDeviceArray);
    }

  }

  return iodevices;
}
bool IODeviceService::validateJsonDocument(QJsonDocument &jsonDocument) {
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
QVector<IODevice *> IODeviceService::addProximitiesToArray(const QJsonArray &jsonArray) {
  QVector<IODevice *> proximities;

  for (const auto &i : jsonArray) {
    QJsonObject ioDeviceObject = i.toObject();
    if (ioDeviceObject.contains("id")) {
      auto detectSensor = new DetectionSensor(ioDeviceObject["id"].toInt(),
                                              ioDeviceObject["low"].toInt() == 1 ? IODevice::LOW : IODevice::HIGH);
      proximities.append(detectSensor);
    }
  }

  return proximities;
}
QVector<IODevice *> IODeviceService::addRelaysToArray(const QJsonArray &jsonArray) {
  QVector<IODevice *> relays;

  for (const auto &i : jsonArray) {
    QJsonObject ioDeviceObject = i.toObject();
    if (ioDeviceObject.contains("id")) {
      auto relay = new Relay(ioDeviceObject["id"].toInt(),
                             ioDeviceObject["low"].toInt() == 1 ? IODevice::LOW : IODevice::HIGH);
      relays.append(relay);
    }
  }

  return relays;
}