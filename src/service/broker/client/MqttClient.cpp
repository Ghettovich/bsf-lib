#include "MqttClient.h"

#include <QString>
#include <QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>

MqttClient::MqttClient(QObject *parent, const QString &host)
    : QObject(parent) {
  m_client = new QMqttClient(this);
  m_client->setPort(1883);

  if (!host.isEmpty()) {
    m_client->setHostname(host);
  } else {
    m_client->setHostname("localhost");
  }

  connect(m_client, &QMqttClient::stateChanged, this, &MqttClient::onStateChanged);
  connect(m_client, &QMqttClient::disconnected, this, &MqttClient::onBrokerDisconnected);
  connect(m_client, &QMqttClient::messageReceived, this, &MqttClient::onMessageReceived);

  connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
    const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(" PingResponse")
        + QLatin1Char('\n');
    qDebug() << content;
  });
}

QMqttClient::ClientState MqttClient::getClientState() const {
  return m_client->state();
}

void MqttClient::connectToHost() {
  if (m_client->state() == QMqttClient::Disconnected &&
      m_client->state() != QMqttClient::Connecting) {
    m_client->connectToHost();
  }
}

void MqttClient::addSubscription(const QString &topic, quint8 QoS) {

  if (!topics.contains(topic)) {
    auto subscription = this->subscription(topic);

    if (!subscription) {
      subscription = m_client->subscribe(topic, QoS);
      topics.append(topic);

      if (!subscription)
        qDebug() << "Error, could not sub D:!";
    }
  }
}

void MqttClient::publishMessage(const QByteArray &message, const QString &topic, quint8 qos) {
  m_client->publish(topic, message, qos, false);
}

QMqttSubscription *MqttClient::subscription(const QString &topic) {
  for (const auto sub : subscriptionList) {
    if (sub->topic().match(topic)) {
      return sub;
      qDebug() << "Found matching sub";
    }
  }

  return nullptr;
}

void MqttClient::onBrokerDisconnected() {
  qDebug() << "Broker disconnected!";
}

void MqttClient::onStateChanged() {
  switch (m_client->state()) {

    case QMqttClient::Disconnected: {
      qDebug() << QLatin1String(": State Change Disconnected ");
      break;
    }
    case QMqttClient::Connecting: {
      qDebug() << QLatin1String(": State Change Connecting ... ");
      break;
    }
    case QMqttClient::Connected: {
      emit brokerConnected();
      qDebug() << QLatin1String(": State Change Connected! ");
      break;
    }
  }
}

void MqttClient::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic) {
  emit receivedSubscriptionData(message, topic.name());

  const QString content = QDateTime::currentDateTime().toString()
      + QLatin1String(" Received Topic: ")
      + topic.name()
      + QLatin1String(" Message: ")
      + message
      + QLatin1Char('\n');
  qDebug() << content;
}
