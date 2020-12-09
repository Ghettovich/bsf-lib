#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <domain/iodevice.h>
#include <domain/arduino.h>
#include <domain/detectionsensor.h>
#include <domain/relay.h>
#include <domain/weightcensor.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class TransformPayload : public QObject {

    Q_OBJECT

public:
    enum ARDUINO_TYPE {
        UNKOWN = 0, BIN_LIFT = 1, WEIGHT_STATION = 2
    };
    Q_ENUM(ARDUINO_TYPE);

    QVector<IODevice *> parseProximitySensors(const QByteArray &payload);
    QVector<IODevice *> parseRelayStates(const QByteArray &payload);


    void updateArduinoWithPayload(int&, Arduino::ARDUINO_STATE&, QVector<IODevice *>&, const QByteArray&);
    ARDUINO_TYPE identifyArduinoWithId(int arduinoId);
    Arduino::ARDUINO_STATE identifyArduinoState(int state);
    void parseIODeviceItemsInPayload(QJsonDocument &, QVector<IODevice *>&);
    IODevice *parseItemWeightStation(QJsonDocument&);
    Recipe addRecipeComponents(QJsonDocument &jsonDocument);
    Component::COMPONENT identifyComponent(int component);

private:
    bool validateJsonDocument(QJsonDocument&);
};
#endif //BSF_TRANSFORMPAYLOAD_H
