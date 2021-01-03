#include "transformpayload.h"
#include <QDebug>

QVector<IODevice *> TransformPayload::parseIODevices(const QByteArray &payload) {
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

WeightSensor *TransformPayload::parseRecipeData(const QByteArray &payload) {
  WeightSensor *weightSensor = nullptr;
  QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));

  if (validateJsonDocument(jsonDocument)) {
    IODevice::IO_DEVICE_HIGH_LOW scaleState;
    scaleState = jsonDocument["low"].toInt() == 0 ? IODevice::LOW : IODevice::HIGH;

    weightSensor = new WeightSensor(jsonDocument["did"].toInt(), scaleState);
    Component component;

    component = Component(jsonDocument["cid"].toInt(), jsonDocument["rid"].toInt());
    component.setCurrentWeight(jsonDocument["weight"].toInt());

    weightSensor->setComponent(component);
  }

  return weightSensor;
}

bool TransformPayload::validateJsonDocument(QJsonDocument &jsonDocument) {
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

QVector<IODevice *> TransformPayload::addProximitiesToArray(const QJsonArray &jsonArray) {
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

QVector<IODevice *> TransformPayload::addRelaysToArray(const QJsonArray &jsonArray) {
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
