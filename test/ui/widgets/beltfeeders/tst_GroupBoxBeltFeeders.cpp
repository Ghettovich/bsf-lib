#include "tst_GroupBoxBeltFeeders.h"
#include <QMetaType>
#include <QFile>
#include <QSignalSpy>
#include <iodevice.h>
#include <widgets/beltfeeders/GroupBoxBeltFeeders.h>

void GroupBoxBeltFeedersTest::init() {
  m_client = new MqttClient(this, host);

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void GroupBoxBeltFeedersTest::isRelayToggledForWidget() {
  qRegisterMetaType<QVector<IODevice *>>();
  auto groupBoxBeltFeeders = new GroupBoxBeltFeeders(m_client);

  quint8 QoS = 0;
  const QString topic = "/relay/states";
  m_client->addIODeviceSubscription(topic, QoS, groupBoxBeltFeeders);

  QSignalSpy spy(m_client, &MqttClient::newIODeviceStates);

  QFile jsonFile(":/payload/relayStates.json");
  jsonFile.open(QIODevice::ReadOnly);
  m_client->onMessageReceived(jsonFile.readAll(), topic);

  QList<QVariant> arguments = spy.takeFirst();
  auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(0));

  QVERIFY(!iodeviceList.isEmpty());
}

void GroupBoxBeltFeedersTest::cleanupTestCase() {

}

QTEST_MAIN(GroupBoxBeltFeedersTest)