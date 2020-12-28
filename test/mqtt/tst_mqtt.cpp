#include <MqttClient.h>
#include <QSignalSpy>
#include <iodevice.h>
#include <weightcensor.h>
#include <QMetaType>
#include <widgets/interfaces/IOWidgetStatusInterface.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>
#include "tst_mqtt.h"

DECLARE_TEST_MQTT(MqttTest)

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

void MqttTest::isRelayStatesEmitted() {
  qRegisterMetaType<QVector<IODevice *>>();
  auto object = new MqttClient(this);

  QSignalSpy spy(object, &MqttClient::newIODeviceStates);
  QMqttTopicName topic("/relay/states");

  QFile jsonFile(":/payload/relayStates.json");
  jsonFile.open(QIODevice::ReadOnly);
  object->onMessageReceived(jsonFile.readAll(), topic);

  QList<QVariant> arguments = spy.takeFirst();
  auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(0));

  QVERIFY(!iodeviceList.isEmpty());
}

void MqttTest::isProximityStatesEmitted() {
  qRegisterMetaType<QVector<IODevice *>>();
  auto object = new MqttClient(this);

  QSignalSpy spy(object, &MqttClient::newIODeviceStates);
  QMqttTopicName topic("/proximity/lift");

  QFile jsonFile(":/payload/proximityStates.json");
  jsonFile.open(QIODevice::ReadOnly);
  object->onMessageReceived(jsonFile.readAll(), topic);

  QList<QVariant> arguments = spy.takeFirst();
  auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(0));

  QVERIFY(!iodeviceList.isEmpty());
}

void MqttTest::isNewRecipeDataEmitted() {
  qRegisterMetaType<WeightSensor *>();
  auto object = new MqttClient(this);

  QObject::connect(object, &MqttClient::newDataForScale,
                   [&](const WeightSensor *value) {
                     QVERIFY(value->getComponent().getRecipeId() != 0);
                     QVERIFY(value->getComponent().getComponentId() != 0);
                     QVERIFY(value->getComponent().getCurrentWeight() != 0);
                   });

  QMqttTopicName topic("/recipe/data");

  QFile jsonFile(":/payload/recipeData.json");
  jsonFile.open(QIODevice::ReadOnly);
  object->onMessageReceived(jsonFile.readAll(), topic);
}

void MqttTest::cleanupTestCase() {

}
