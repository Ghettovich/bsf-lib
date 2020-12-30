#include "tst_IOWidgetStatusInterfaceTest.h"
#include <MqttClient.h>
#include <QMetaType>
#include <QFile>
#include <QSignalSpy>
#include <iodevice.h>
#include <widgets/binloaddrop/GroupBoxBinLoadDrop.h>
#include <widgets/liftupdown/GroupBoxLiftUpDown.h>

DECLARE_TEST_IOWIDGETINTERFACE(IOWidgetStatusInterfaceTest)

void IOWidgetStatusInterfaceTest::initTestCase() {
}

void IOWidgetStatusInterfaceTest::isProximityUpdatedForWidget() {
  // ARRANGE
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
  auto groupBoxLiftUpDown = new GroupBoxLiftUpDown(m_client);

  // ACT
  m_client->addIODeviceSubscription(topic, QoS, groupBoxBinLoadDrop);
  m_client->addIODeviceSubscription(topic, QoS, groupBoxLiftUpDown);

  QFile jsonFile(":/payload/proximityStates.json");
  jsonFile.open(QIODevice::ReadOnly);

  QSignalSpy spyProximityChanged(groupBoxBinLoadDrop, &GroupBoxBinLoadDrop::proximityStateChange);
  QVERIFY(spyProximityChanged.isValid());

  QSignalSpy spyProximityLiftUpDown(groupBoxLiftUpDown, &GroupBoxLiftUpDown::proximityStateChange);
  QVERIFY(spyProximityLiftUpDown.isValid());

  m_client->onMessageReceived(jsonFile.readAll(), topic);
  auto *iodevice = qvariant_cast<IODevice *>(spyProximityChanged.at(0).at(0));

  // ASSERT
  QVERIFY(iodevice->getId() != 0);
  // all states HIGH (defined as PULL UP so 0) in payload
  QVERIFY(iodevice->getDeviceState() == IODevice::HIGH);

  iodevice = qvariant_cast<IODevice *>(spyProximityLiftUpDown.at(0).at(0));

  QVERIFY(iodevice->getId() != 0);
  // all states HIGH (defined as PULL UP so 0) in payload
  QVERIFY(iodevice->getDeviceState() == IODevice::HIGH);
}

void IOWidgetStatusInterfaceTest::isRelayToggledForWidget() {
  // ARRANGE
  qRegisterMetaType<IODevice *>();
  qRegisterMetaType<IODevice::IO_DEVICE_HIGH_LOW>();
  const QString mqttHost = "192.168.178.5";
  auto m_client = new MqttClient(this, mqttHost);

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  m_client->connectToHost();
  QVERIFY(spy.wait(1000));

  quint8 QoS = 0;
  const QString topic = "/relay/states";
  auto groupBoxBinLoadDrop = new GroupBoxBinLoadDrop(m_client);
  auto groupBoxLiftUpDown = new GroupBoxLiftUpDown(m_client);

  // ACT
  m_client->addIODeviceSubscription(topic, QoS, groupBoxBinLoadDrop);
  m_client->addIODeviceSubscription(topic, QoS, groupBoxLiftUpDown);

  QFile jsonFile(":/payload/relayStates.json");
  jsonFile.open(QIODevice::ReadOnly);

  QSignalSpy spyRelayToggledBin(groupBoxBinLoadDrop, &GroupBoxBinLoadDrop::toggledRelay);
  QVERIFY(spyRelayToggledBin.isValid());

  QSignalSpy spyRelayToggledLift(groupBoxLiftUpDown, &GroupBoxLiftUpDown::toggledRelay);
  QVERIFY(spyRelayToggledLift.isValid());

  m_client->onMessageReceived(jsonFile.readAll(), topic);
  auto *iodevice = qvariant_cast<IODevice *>(spyRelayToggledBin.at(0).at(0));

  // ASSERT
  QVERIFY(iodevice->getId() != 0);
  // all states HIGH (defined as PULL UP so 0) in payload
  QVERIFY(iodevice->getDeviceState() == IODevice::HIGH);

  iodevice = qvariant_cast<IODevice *>(spyRelayToggledLift.at(0).at(0));

  QVERIFY(iodevice->getId() != 0);
  // all states HIGH (defined as PULL UP so 0) in payload
  QVERIFY(iodevice->getDeviceState() == IODevice::HIGH);
}

void IOWidgetStatusInterfaceTest::cleanupTestCase() {

}
