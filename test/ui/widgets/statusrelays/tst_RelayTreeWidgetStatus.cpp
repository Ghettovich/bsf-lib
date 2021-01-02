#include "tst_RelayTreeWidgetStatus.h"
#include <QSignalSpy>
#include <iodevice.h>
#include <QFile>
#include <widgets/statusrelays/RelayTreeWidget.h>

void RelayTreeWidgetTest::init() {
  m_client = new MqttClient(this, host);

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void RelayTreeWidgetTest::isRelayToggledForWidget() {
  qRegisterMetaType<QVector<IODevice *>>();
  auto statusRelayTreeWidget = new RelayTreeWidget;

  quint8 QoS = 0;
  const QString topicRelayStates("/relay/states");

  m_client->addIODeviceSubscription(topicRelayStates, QoS, statusRelayTreeWidget);

  QSignalSpy spy(m_client, &MqttClient::newIODeviceStates);
  QMqttTopicName topic("/relay/states");

  QFile jsonFile(":/payload/relayStatesHighLow.json");
  jsonFile.open(QIODevice::ReadOnly);
  m_client->onMessageReceived(jsonFile.readAll(), topicRelayStates);

  QList<QVariant> arguments = spy.takeFirst();
  auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(0));

  QVERIFY(!iodeviceList.isEmpty());
}

void RelayTreeWidgetTest::cleanupTestCase() {

}

QTEST_MAIN(RelayTreeWidgetTest)
