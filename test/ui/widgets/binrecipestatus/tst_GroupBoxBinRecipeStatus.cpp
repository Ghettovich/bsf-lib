#include "tst_GroupBoxBinRecipeStatus.h"
#include <QMetaType>
#include <QFile>
#include <QSignalSpy>
#include <weightcensor.h>
#include <widgets/binrecipestatus/GroupBoxBinRecipeStatus.h>

void GroupBoxBinRecipeStatusTest::init() {
  m_client = new MqttClient(this, host);

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void GroupBoxBinRecipeStatusTest::updateTableWidgetWithComponent() {
  // ARRANGE
  qRegisterMetaType<Component>();
  qRegisterMetaType<WeightSensor *>();

  quint8 QoS = 0;
  const QString topic = "/recipe/data";
  auto groupBoxBinLoadDrop = new GroupBoxBinRecipeStatus(m_client);

  // ACT
  m_client->addRecipeDataSubscription(QoS, groupBoxBinLoadDrop);

  QFile jsonFile(":/payload/recipeData.json");
  jsonFile.open(QIODevice::ReadOnly);
  const QByteArray payload = jsonFile.readAll();

  QSignalSpy spy(m_client, &MqttClient::newDataForScale);
  QVERIFY(spy.isValid());

  m_client->onMessageReceived(payload, topic);

  auto weightSensor = qvariant_cast<WeightSensor *>(spy.at(0).at(0));
  QVERIFY(weightSensor->getComponent().getComponentId() != 0);

  groupBoxBinLoadDrop->onUpdateIODevice(weightSensor);
  groupBoxBinLoadDrop->onUpdateIODevice(weightSensor);

  QVERIFY(weightSensor->getComponent().getComponentId() != 0);
  QVERIFY(weightSensor->getComponent().getRecipeId() != 0);
  QVERIFY(weightSensor->getComponent().getCurrentWeight() >= 0);
}

void GroupBoxBinRecipeStatusTest::cleanupTestCase() {

}

QTEST_MAIN(GroupBoxBinRecipeStatusTest)