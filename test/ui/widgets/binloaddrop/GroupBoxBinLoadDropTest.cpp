#include "GroupBoxBinLoadDropTest.h"
#include <QMetaType>
#include <QFile>
#include <QSignalSpy>
#include <iodevice.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>

void GroupBoxBinLoadDropTest::init() {
  m_client = new MqttClient(this, host);
  
  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void GroupBoxBinLoadDropTest::isProximityUpdatedForWidget() {
  // ARRANGE
  qRegisterMetaType<IODevice *>();
  qRegisterMetaType<IODevice::IO_DEVICE_HIGH_LOW>();

  quint8 QoS = 0;
  const QString topic = "/proximity/lift";
  auto groupBoxBinLoadDrop = new GroupBoxBinLoadDrop(m_client);

  // ACT
  m_client->addIODeviceSubscription(topic, QoS, groupBoxBinLoadDrop);

  QFile jsonFile(":/payload/proximityStates.json");
  jsonFile.open(QIODevice::ReadOnly);

  QSignalSpy spyProximityChanged(groupBoxBinLoadDrop, &GroupBoxBinLoadDrop::proximityStateChange);
  QVERIFY(spyProximityChanged.isValid());

  m_client->onMessageReceived(jsonFile.readAll(), topic);
  auto iodevice = qvariant_cast<IODevice *>(spyProximityChanged.at(0).at(0));

  // ASSERT
  QVERIFY(iodevice->getId() != 0);
  // all states HIGH (defined as PULL UP so 0) in payload
  QVERIFY(iodevice->getDeviceState() == IODevice::HIGH);
}

void GroupBoxBinLoadDropTest::isRelayToggledForWidget() {
  // ARRANGE
  qRegisterMetaType<IODevice *>();
  qRegisterMetaType<IODevice::IO_DEVICE_HIGH_LOW>();

  quint8 QoS = 0;
  const QString topic = "/relay/states";
  auto groupBoxBinLoadDrop = new GroupBoxBinLoadDrop(m_client);

  // ACT
  m_client->addIODeviceSubscription(topic, QoS, groupBoxBinLoadDrop);

  QFile jsonFile(":/payload/relayStates.json");
  jsonFile.open(QIODevice::ReadOnly);

  QSignalSpy spyRelayToggled(groupBoxBinLoadDrop, &GroupBoxBinLoadDrop::toggledRelay);
  QVERIFY(spyRelayToggled.isValid());

  m_client->onMessageReceived(jsonFile.readAll(), topic);
  auto iodevice = qvariant_cast<IODevice *>(spyRelayToggled.at(0).at(0));

  // ASSERT
  QVERIFY(iodevice->getId() != 0);
  // all states HIGH (defined as PULL UP so 0) in payload
  QVERIFY(iodevice->getDeviceState() == IODevice::HIGH);
}

void GroupBoxBinLoadDropTest::cleanupTestCase() {

}

QTEST_MAIN(GroupBoxBinLoadDropTest)
