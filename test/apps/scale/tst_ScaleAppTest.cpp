#include "tst_ScaleAppTest.h"
#include <QMetaType>
#include <QFile>
#include <QSignalSpy>
#include <weightcensor.h>
#include <main/MainWindow.h>

void ScaleAppTest::init() {
  m_client = new MqttClient(this, host);

  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void ScaleAppTest::configureScaleWithPayload() {
  qRegisterMetaType<WeightSensor *>();
  auto scaleApp = new MainWindow(m_client);

  QFile jsonFile(":/payload/recipeData.json");
  jsonFile.open(QIODevice::ReadOnly);
  const QByteArray payload = jsonFile.readAll();

  QSignalSpy spy(m_client, &MqttClient::newDataForScale);
  QVERIFY(spy.isValid());

  scaleApp->onClickPushButtonChangeRecipe();

  const QString topic = "/recipe/data";
  m_client->onMessageReceived(payload, topic);

  auto weightSensor = qvariant_cast<WeightSensor *>(spy.at(0).at(0));
  QVERIFY(weightSensor->getComponent().getComponentId() != 0);
}

void ScaleAppTest::updateWidgetComponentSelectionChanged() {
  qRegisterMetaType<WeightSensor *>();
  auto scaleApp = new MainWindow(m_client);

  QFile jsonFile(":/payload/recipeComponentUpdated.json");
  jsonFile.open(QIODevice::ReadOnly);
  const QByteArray payload = jsonFile.readAll();

  QSignalSpy spy(m_client, &MqttClient::newDataForScale);
  QVERIFY(spy.isValid());

  scaleApp->onClickPushButtonChangeRecipe();
  scaleApp->onClickPushButtonComponentDown();

  const QString topic = "/recipe/data";
  m_client->onMessageReceived(payload, topic);

  auto weightSensor = qvariant_cast<WeightSensor *>(spy.at(0).at(0));
  QVERIFY(weightSensor->getComponent().getComponentId() != 0);
}

void ScaleAppTest::cleanupTestCase() {

}

QTEST_MAIN(ScaleAppTest)