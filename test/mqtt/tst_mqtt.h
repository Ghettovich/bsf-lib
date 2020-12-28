#ifndef BSF_LIB_TEST_MQTT_TST_MQTT_H_
#define BSF_LIB_TEST_MQTT_TST_MQTT_H_

#include "../autotest/AutoTest.h"
#include <QtTest/QTest>
#include <QtCore/QObject>

class MqttTest: public QObject {
  Q_OBJECT

 private slots:
  void initTestCase();
  void isConnectedToBroker();
  void cleanupTestCase();
};

#endif //BSF_LIB_TEST_MQTT_TST_MQTT_H_
