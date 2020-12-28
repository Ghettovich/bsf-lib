#ifndef BSF_LIB_TEST_MQTT_TST_MQTT_H_
#define BSF_LIB_TEST_MQTT_TST_MQTT_H_

#include "../autotest/AutoTest.h"
#include <QtTest/QTest>
#include <QtCore/QObject>
#include <QMetaType>
#include <iodevice.h>
#include <weightcensor.h>

class MqttTest: public QObject {
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
