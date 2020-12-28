#include <MqttClient.h>
#include <QSignalSpy>
#include "tst_mqtt.h"

void MqttTest::initTestCase() {

}

void MqttTest::isConnectedToBroker() {
  // ARRANGE
  auto parent = new QObject;
  auto m_client = new MqttClient(parent, "192.168.178.5");

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void MqttTest::cleanupTestCase() {

}
