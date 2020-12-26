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

  QVector<IODevice *> parseIODevices(const QByteArray &payload);
  WeightSensor *parseRecipeData(const QByteArray &payload);

 private:
  bool validateJsonDocument(QJsonDocument &);
  QVector<IODevice *> addProximitiesToArray(const QJsonArray &jsonArray);
  QVector<IODevice *> addRelaysToArray(const QJsonArray &jsonArray);
};
#endif //BSF_TRANSFORMPAYLOAD_H
