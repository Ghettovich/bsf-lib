#include "BrokerService.h"

#include <QSettings>
#include <QtCore/QJsonObject>

using namespace service;

BrokerService::BrokerService(QObject *parent) : QObject(parent) {
  m_client = std::make_unique<MqttClient>(this, getHost(parent));

  connect(m_client.get(), &MqttClient::brokerConnected, [=](){
    emit connectedToHost();
  });

  connect(m_client.get(), &MqttClient::receivedSubscriptionData, [=](const QByteArray &message, const QString &topic){
    emit newMessageForTopic(message, topic);
  });
}

QString BrokerService::getHost(QObject *parent) {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, parent);
  settings->beginGroup("mqtt_server");

  qDebug() << "Host = " << settings->value("host").toString();

  return settings->value("host").toString();
}

void BrokerService::connectToHost() {
  m_client->connectToHost();
}

void BrokerService::addSubscription(const QString &topic, quint8 qos) {
  m_client->addSubscription(topic, qos);
}
void BrokerService::toggleRelay(int relayId) {
  quint8 qos = 1;
  QJsonObject jsonPayload;
  jsonPayload["toggle"] = relayId;

  auto doc = QJsonDocument(jsonPayload);

  m_client->publishMessage(doc.toJson(), toggleRelayTopic, qos);
}
void BrokerService::configureRecipe(int recipeId, int componentId, int targetWeight) {
  quint8 qos = 1;
  QJsonObject jsonPayloadObject;
  jsonPayloadObject["recipeId"] = recipeId;
  jsonPayloadObject["componentId"] = componentId;
  jsonPayloadObject["targetWeight"] = targetWeight;

  auto doc = QJsonDocument(jsonPayloadObject);

  m_client->publishMessage(doc.toJson(), configureRecipeTopic, qos);
}

