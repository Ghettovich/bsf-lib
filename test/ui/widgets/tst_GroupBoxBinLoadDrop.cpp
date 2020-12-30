#include "tst_GroupBoxBinLoadDrop.h"
#include <MqttClient.h>
#include <QMetaType>
#include <QFile>
#include <QSignalSpy>
#include <iodevice.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>

DECLARE_TEST_GROUPBOX_BINLOADDROP(GroupBoxBinLoadDropTest)

void GroupBoxBinLoadDropTest::initTestCase() {
}

void GroupBoxBinLoadDropTest::isProximityUpdatedForWidget() {
  qRegisterMetaType<IODevice *>();
  qRegisterMetaType<IODevice::IO_DEVICE_HIGH_LOW>();
  const QString mqttHost = "192.168.178.5";
  auto m_client = new MqttClient(this, mqttHost);

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  quint8 QoS = 0;
  const QString topic = "/proximity/lift";
  auto groupBoxBinLoadDrop = new GroupBoxBinLoadDrop(m_client);
  m_client->addIODeviceSubscription(topic, QoS, groupBoxBinLoadDrop);

  QFile jsonFile(":/payload/proximityStates.json");
  jsonFile.open(QIODevice::ReadOnly);

  QSignalSpy spyProximityChanged(groupBoxBinLoadDrop, &GroupBoxBinLoadDrop::proximityStateChange);
  QVERIFY(spyProximityChanged.isValid());

  m_client->onMessageReceived(jsonFile.readAll(), topic);
  auto *iodevice = qvariant_cast<IODevice *>(spyProximityChanged.at(0).at(0));

  QVERIFY(iodevice->getId() != 0);
  // all states HIGH (defined as PULL UP so 0) in payload
  QVERIFY(iodevice->getDeviceState() == IODevice::HIGH);
}

void GroupBoxBinLoadDropTest::isRelayToggledForWidget() {
  qRegisterMetaType<IODevice *>();
  qRegisterMetaType<IODevice::IO_DEVICE_HIGH_LOW>();
  const QString mqttHost = "192.168.178.5";
  auto m_client = new MqttClient(this, mqttHost);

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  quint8 QoS = 0;
  const QString topic = "/relay/states";
  auto groupBoxBinLoadDrop = new GroupBoxBinLoadDrop(m_client);
  m_client->addIODeviceSubscription(topic, QoS, groupBoxBinLoadDrop);

  QFile jsonFile(":/payload/relayStates.json");
  jsonFile.open(QIODevice::ReadOnly);

  QSignalSpy spyRelayToggled(groupBoxBinLoadDrop, &GroupBoxBinLoadDrop::toggledRelay);
  QVERIFY(spyRelayToggled.isValid());

  m_client->onMessageReceived(jsonFile.readAll(), topic);
  auto *iodevice = qvariant_cast<IODevice *>(spyRelayToggled.at(0).at(0));

  QVERIFY(iodevice->getId() != 0);
  // all states HIGH (defined as PULL UP so 0) in payload
  QVERIFY(iodevice->getDeviceState() == IODevice::HIGH);
}

void GroupBoxBinLoadDropTest::cleanupTestCase() {

}
