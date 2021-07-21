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

  devices = deviceRepository->findAllDevices();

  connect(brokerService.get(), &BrokerService::newMessageForTopic,
          this, &IODeviceService::onNewIODeviceStates);
}
QVector<IODevice *> IODeviceService::findAllDevices() {
  return devices;
}
QVector<IODevice *> IODeviceService::findAllDevices(IODeviceType::IO_DEVICE_TYPE deviceType) {
  QVector<IODevice *> devicesWithType;

  for (const auto &device: devices) {
    if (device->getDeviceType() == deviceType) {
      devicesWithType.append(device);
    }
  }

  return devicesWithType;
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
  QVector<IODevice *> relayDevices;

  relayDevices = parseIODevices(message);

  updateDevices(relayDevices);

  emit updateRelayDevices(relayDevices);
}
void IODeviceService::parseProximityStates(const QByteArray &message) {
  QVector<IODevice *> proximityDevices;

  proximityDevices = parseIODevices(message);

  updateDevices(proximityDevices);

  emit updateProximityDevices(proximityDevices);
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

    updateDevices(weightSensor);

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
void IODeviceService::updateDevices(IODevice *_device) {
  auto weightSensor = dynamic_cast<WeightSensor*>(_device);

  if(weightSensor) {

    for (const auto &device:devices) {
      if (device->getId() == _device->getId()) {

        auto deviceToUpdate = dynamic_cast<WeightSensor *>(device);

        deviceToUpdate->setDeviceState(_device->getDeviceState());
        deviceToUpdate->setRecipeId(weightSensor->getRecipeId());
        deviceToUpdate->setComponentId(weightSensor->getComponentId());
        deviceToUpdate->setCurrentWeight(weightSensor->getCurrentWeight());

        qDebug() << "Updated weight sensor in device list";
        break;
      }
    }

  }
}
void IODeviceService::updateDevices(const QVector<IODevice *> &_devices) {

  for (const auto &deviceToUpdate : devices) {

    for (const auto &device: _devices) {
      if(device->getId() == deviceToUpdate->getId()) {
        deviceToUpdate->setDeviceState(device->getDeviceState());

        qDebug() << "Updated device in device list";
        break;
      }
    }
  }
}
