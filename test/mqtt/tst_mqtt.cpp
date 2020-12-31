#include <MqttClient.h>
#include <QSignalSpy>
#include <iodevice.h>
#include <weightcensor.h>
#include <QMetaType>
#include <widgets/interfaces/IOWidgetStatusInterface.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>
#include "tst_mqtt.h"

void MqttClientTest::initTestCase() {
}

void MqttClientTest::isConnectedToBroker() {
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

void MqttClientTest::isRelayStatesEmitted() {
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

void MqttClientTest::isProximityStatesEmitted() {
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

void MqttClientTest::isNewRecipeDataEmitted() {
  qRegisterMetaType<WeightSensor *>();
  auto object = new MqttClient(this);

  QSignalSpy spy(object, &MqttClient::newDataForScale);
  QMqttTopicName topic("/recipe/data");

  QFile jsonFile(":/payload/recipeData.json");
  jsonFile.open(QIODevice::ReadOnly);
  object->onMessageReceived(jsonFile.readAll(), topic);

  auto *iodevice = qvariant_cast<WeightSensor *>(spy.at(0).at(0));

  QVERIFY(iodevice->getComponent().getRecipeId() != 0);
  QVERIFY(iodevice->getComponent().getComponentId()!= 0);
  QVERIFY(iodevice->getComponent().getCurrentWeight()!= 0);
}

void MqttClientTest::cleanupTestCase() {

}

QTEST_MAIN(MqttClientTest)
