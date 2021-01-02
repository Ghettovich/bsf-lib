#include "tst_Scale.h"
#include <QFile>
#include <QSignalSpy>
#include <QMetaType>
#include <component.h>
#include <weightcensor.h>
#include <widgets/scale/Scale.h>

void ScaleTest::init() {
  m_client = new MqttClient(this, host);
  QSignalSpy spy(m_client, &MqttClient::brokerConnected);
  QVERIFY(spy.isValid());

  // ACT
  m_client->connectToHost();
  QVERIFY(spy.wait(1001));

  // ASSERT
  QCOMPARE(spy.count(), 1);
}

void ScaleTest::isActiveComponentEmitted() {
  qRegisterMetaType<Component>();
  qRegisterMetaType<WeightSensor *>();
  quint8 QoS = 0;

  auto scale = new Scale(m_client);
  m_client->addRecipeDataSubscription(QoS, scale);

  QFile jsonFile(":/payload/recipeData.json");
  jsonFile.open(QIODevice::ReadOnly);
  const QByteArray payload = jsonFile.readAll();

  QSignalSpy spy(m_client, &MqttClient::newDataForScale);
  QVERIFY(spy.isValid());

  QSignalSpy spyReceivedComponent(scale, &Scale::receivedComponent);
  QVERIFY(spy.isValid());

  const QString topic = "/recipe/data";
  m_client->onMessageReceived(payload, topic);

  auto weightSensor = qvariant_cast<WeightSensor *>(spy.at(0).at(0));
  QVERIFY(weightSensor->getComponent().getComponentId() != 0);

  auto component = qvariant_cast<Component>(spyReceivedComponent.at(0).at(0));

  QVERIFY(component.getComponentId() != 0);
  QVERIFY(component.getRecipeId() != 0);
  QVERIFY(component.getCurrentWeight() >= 0);
}

void ScaleTest::isComponentSelectionChanged() {
  qRegisterMetaType<Component>();
  qRegisterMetaType<WeightSensor *>();
  quint8 QoS = 0;

  auto scale = new Scale(m_client);
  m_client->addRecipeDataSubscription(QoS, scale);

  QFile jsonFile(":/payload/recipeComponentUpdated.json");
  jsonFile.open(QIODevice::ReadOnly);
  const QByteArray payload = jsonFile.readAll();

  QSignalSpy spy(m_client, &MqttClient::newDataForScale);
  QVERIFY(spy.isValid());

  QSignalSpy spyReceivedComponent(scale, &Scale::receivedComponent);
  QVERIFY(spy.isValid());

  const QString topic = "/recipe/data";
  m_client->onMessageReceived(payload, topic);

  auto weightSensor = qvariant_cast<WeightSensor *>(spy.at(0).at(0));
  QVERIFY(weightSensor->getComponent().getComponentId() != 0);

  auto component = qvariant_cast<Component>(spyReceivedComponent.at(0).at(0));

  QVERIFY(component.getComponentId() != 0);
  QVERIFY(component.getRecipeId() != 0);
  QVERIFY(component.getCurrentWeight() >= 0);
}

void ScaleTest::isTareActivated() {
  qRegisterMetaType<Component>();
  qRegisterMetaType<WeightSensor *>();
  quint8 QoS = 0;

  auto scale = new Scale(m_client);
  m_client->addRecipeDataSubscription(QoS, scale);

  QFile jsonFile(":/payload/tarePayload.json");
  jsonFile.open(QIODevice::ReadOnly);
  const QByteArray payload = jsonFile.readAll();

  QSignalSpy spyReceivedComponent(scale, SIGNAL(scaleInTareMode(bool)));
  QVERIFY(spyReceivedComponent.isValid());

  const QString topic = "/recipe/data";
  m_client->onMessageReceived(payload, topic);

  QList<QVariant> arguments = spyReceivedComponent.takeFirst();
  QVERIFY(arguments.at(0).type() == QVariant::Bool);
}

void ScaleTest::cleanupTestCase() {
}

QTEST_MAIN(ScaleTest)