#include "transformpayload.h"

QVector<IODevice *> TransformPayload::parseProximitySensors(const QByteArray &payload)
{
    QVector<IODevice *> proximities;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));

    if(validateJsonDocument(jsonDocument)) {
        QJsonArray proximitiesArray(jsonDocument["proximities"].toArray());

        for (int i = 0; i < proximitiesArray.size(); i++) {
            QJsonObject ioDeviceObject = proximitiesArray[i].toObject();
            if (ioDeviceObject.contains("id")) {
                auto detectSensor = new DetectionSensor(ioDeviceObject["id"].toInt(),
                                                        ioDeviceObject["low"].toInt() == 1 ? IODevice::LOW : IODevice::HIGH);
                proximities.append(detectSensor);
            }
        }
    }

    return proximities;
}

QVector<IODevice *> TransformPayload::parseRelayStates(const QByteArray &payload)
{
    QVector<IODevice *> relays;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));

    if(validateJsonDocument(jsonDocument)) {
        QJsonArray relayArray(jsonDocument["relays"].toArray());

        for (int i = 0; i < relayArray.size(); i++) {
            QJsonObject ioDeviceObject = relayArray[i].toObject();
            if (ioDeviceObject.contains("id")) {
                auto relay = new Relay(ioDeviceObject["id"].toInt(),
                                                        ioDeviceObject["low"].toInt() == 1 ? IODevice::LOW : IODevice::HIGH);
                relays.append(relay);
            }
        }
    }

    return relays;
}

WeightSensor *TransformPayload::parseRecipeData(const QByteArray &payload)
{
    WeightSensor *weightSensor = nullptr;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));

    if(validateJsonDocument(jsonDocument)) {
        Component component;

        component = Component(jsonDocument["cid"].toInt()
            ,jsonDocument["rid"].toInt());
        component.setCurrentWeight(jsonDocument["weight"].toInt());

        weightSensor = new WeightSensor(component);
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

    return true;
}
