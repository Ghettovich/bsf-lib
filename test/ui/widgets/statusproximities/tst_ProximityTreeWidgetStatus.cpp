#include "tst_ProximityTreeWidgetStatus.h"
#include <QSignalSpy>
#include <iodevice.h>
#include <QFile>
#include <widgets/statusproximities/ProximityTreeWidget.h>

void ProximityTreeWidgetStatusTest::init() {
  m_client = new MqttClient(this, host);

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void ProximityTreeWidgetStatusTest::isProximityToggledForWidget() {
  qRegisterMetaType<QVector<IODevice *>>();
  auto statusRelayTreeWidget = new ProximityTreeWidget;

  quint8 QoS = 0;
  const QString topicProximityLift("/proximity/lift");

  m_client->addIODeviceSubscription(topicProximityLift, QoS, statusRelayTreeWidget);

  QSignalSpy spy(m_client, &MqttClient::newIODeviceStates);
  QVERIFY(spy.isValid());

  QFile jsonFile(":/payload/proximityHighLow.json");
  jsonFile.open(QIODevice::ReadOnly);
  m_client->onMessageReceived(jsonFile.readAll(), topicProximityLift);

  QList<QVariant> arguments = spy.takeFirst();
  auto iodeviceList = qvariant_cast<QVector<IODevice *>>(arguments.at(0));

  QVERIFY(!iodeviceList.isEmpty());
}

void ProximityTreeWidgetStatusTest::cleanupTestCase() {
}

QTEST_MAIN(ProximityTreeWidgetStatusTest)