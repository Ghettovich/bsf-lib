#ifndef BSF_LIB_TEST_MQTT_TST_MQTT_H_
#define BSF_LIB_TEST_MQTT_TST_MQTT_H_

#include <QObject>
#include <QTest>
#include <iodevice.h>
#include <weightcensor.h>

class MqttClientTest: public QObject {
  Q_OBJECT

 private slots:
  void initTestCase();
  void isConnectedToBroker();
  void isRelayStatesEmitted();
  void isProximityStatesEmitted();
  void isNewRecipeDataEmitted();
  void cleanupTestCase();
};

#endif //BSF_LIB_TEST_MQTT_TST_MQTT_H_
