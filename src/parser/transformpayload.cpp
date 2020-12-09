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

void TransformPayload::updateArduinoWithPayload(int &_arduinoId, Arduino::ARDUINO_STATE &newState,
                                                QVector<IODevice *> &ioDeviceList, const QByteArray &payload) {
    QString errorMsg;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));
    QJsonValue arduinoId(jsonDocument["arduinoId"].toInt());

    if (validateJsonDocument(jsonDocument)) {
        _arduinoId = arduinoId.toInt();
        TransformPayload::ARDUINO_TYPE type = identifyArduinoWithId(_arduinoId);

        if (type != ARDUINO_TYPE::UNKOWN) {
            QJsonValue state(jsonDocument["state"]);
            newState = identifyArduinoState(state.toInt());

            // Parse io device items
            parseIODeviceItemsInPayload(jsonDocument, ioDeviceList);
        }
    }
}

/*
 * Parse a json document to an IODevice vector list.
 * Both detection sensor and relay are LOW when power is on. e.g. When the detectionsensors is able to
 * see the bin they are LOW. When power flows through the relay they are LOW.
 * Weightsensors are digital. When HIGH it means they are active and a recipe is in progress.
 * */
void TransformPayload::parseIODeviceItemsInPayload(QJsonDocument &jsonDocument, QVector<IODevice *> &ioDeviceList) {
    QJsonObject jsonObject(jsonDocument["iodevices"].toObject());
    QJsonArray items = jsonObject["items"].toArray();

    for (int i = 0; i < items.size(); i++) {
        QJsonObject ioDeviceObject = items[i].toObject();
        if (ioDeviceObject.contains("id")) {

            if (ioDeviceObject["typeId"].toInt() == 1) {
                auto weightSensor = new WeightSensor(ioDeviceObject["id"].toInt(),
                                                     ioDeviceObject["low"].toInt() == 0 ? IODevice::HIGH : IODevice::LOW);
                ioDeviceList.append(weightSensor);
            } else if (ioDeviceObject["typeId"].toInt() == 2) {
                auto detectSensor = new DetectionSensor(ioDeviceObject["id"].toInt(),
                                                        ioDeviceObject["low"].toInt() == 0 ? IODevice::HIGH : IODevice::LOW);
                ioDeviceList.append(detectSensor);
            } else if (ioDeviceObject["typeId"].toInt() == 3) {
                auto relay = new Relay(ioDeviceObject["id"].toInt(),
                                       ioDeviceObject["low"].toInt() == 0 ? IODevice::HIGH : IODevice::LOW);
                ioDeviceList.append(relay);
            }
        }
    }
}

IODevice *TransformPayload::parseItemWeightStation(QJsonDocument &jsonDocument) {
    IODevice *ioDevice;
    QJsonValue iodeviceId(jsonDocument["iodeviceId"]);
    QJsonValue jsonValueLow(jsonDocument["low"]);

    if (jsonDocument["typeId"].toInt() == IODeviceType::WEIGHTSENSOR) {
        // REMEMBER!! scale is DIGITAL input, HIGH means ON and LOW if OFF
        IODevice::IO_DEVICE_HIGH_LOW low = jsonValueLow.toInt() == 0 ? IODevice::LOW : IODevice::HIGH;
        ioDevice = new WeightSensor(iodeviceId.toInt(), low);
        return ioDevice;
    }

    printf("Could not determine iodevice type");
    return nullptr;
}

Recipe TransformPayload::addRecipeComponents(QJsonDocument &jsonDocument) {
    QJsonValue recipeId(jsonDocument["recipeId"]);
    Recipe recipe = Recipe(recipeId.toInt());

    QJsonValue selectedComponent(jsonDocument["selecComp"]);
    Component::COMPONENT selectedComp = identifyComponent(selectedComponent.toInt());
    recipe.setSelectedComponent(selectedComp);

    QJsonArray jsonArray(jsonDocument["components"].toArray());

    for (auto &&i : jsonArray) {
        QJsonObject ioDeviceObject = i.toObject();

        if (ioDeviceObject.contains("id")) {
            Component comp(ioDeviceObject["id"].toInt());
            comp.setTargetWeight(ioDeviceObject["weight"].toInt());
            recipe.componentList.append(comp);
        }
    }

    return recipe;
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

TransformPayload::ARDUINO_TYPE TransformPayload::identifyArduinoWithId(int arduinoId) {
    switch (arduinoId) {
        case ARDUINO_TYPE::BIN_LIFT :
            return ARDUINO_TYPE::BIN_LIFT;
        case ARDUINO_TYPE::WEIGHT_STATION :
            return ARDUINO_TYPE::WEIGHT_STATION;
        default:
            return ARDUINO_TYPE::UNKOWN;
    }
}

Arduino::ARDUINO_STATE TransformPayload::identifyArduinoState(int state) {
    switch (state) {
        case Arduino::READY :
            return Arduino::READY;
        case Arduino::LIFT_ASC :
            return Arduino::LIFT_ASC;
        case Arduino::LIFT_DESC :
            return Arduino::LIFT_DESC;
        case Arduino::BIN_LOADING :
            return Arduino::BIN_LOADING;
        case Arduino::BIN_DUMPING :
            return Arduino::BIN_DUMPING;
        case Arduino::RECIPE_SET :
            return Arduino::RECIPE_SET;
        case Arduino::RECIPE_TARGETS_MET :
            return Arduino::RECIPE_TARGETS_MET;
        default:
            return Arduino::UNKOWN;
    }
}
Component::COMPONENT TransformPayload::identifyComponent(int component) {
    switch (component) {
        case Component::WATER :
            return Component::WATER;
        case Component::SAND :
            return Component::SAND;
        case Component::PLASTIFIER :
            return Component::PLASTIFIER;
        default:
            return Component::UNKNOWN_COMP;
    }
}
