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

void MqttClient::publishToggleRelay(int relayId) {
  quint8 QoS = 1;
  QJsonObject jsonPayload;
  jsonPayload["toggle"] = relayId;

  doc = QJsonDocument(jsonPayload);

  if (m_client->publish(toggleRelayTopic,
                        doc.toJson(),
                        QoS,
                        false) == -1) {
  }
}

void MqttClient::publishConfirmComponent(int recipeId, int componentId) {
  quint8 QoS = 1;
  QJsonObject jsonPayload;
  jsonPayload["recipeId"] = recipeId;
  jsonPayload["componentId"] = componentId;
  jsonPayload["confirm"] = true;

  doc = QJsonDocument(jsonPayload);

  if (m_client->publish(configureRecipeTopic,
                        doc.toJson(),
                        QoS,
                        false) == -1) {
  }
}

void MqttClient::publishTareScale(bool confirm, int calibrationWeight) {
  quint8 QoS = 1;
  QJsonObject jsonPayload;
  jsonPayload["tare"] = confirm;
  jsonPayload["weight"] = calibrationWeight;

  doc = QJsonDocument(jsonPayload);

  if (m_client->publish(tareScaleTopic,
                        doc.toJson(),
                        QoS,
                        false) == -1) {
  }
}

void MqttClient::publishRecipe(int recipeId, int componentId, int targetWeight) {
  quint8 QoS = 1;
  QJsonObject jsonPayloadObject;
  jsonPayloadObject["recipeId"] = recipeId;
  jsonPayloadObject["componentId"] = componentId;
  jsonPayloadObject["targetWeight"] = targetWeight;

  doc = QJsonDocument(jsonPayloadObject);

  if (m_client->publish(configureRecipeTopic,
                        doc.toJson(),
                        QoS,
                        false) == -1) {
  }
}

void MqttClient::addIODeviceSubscription(const QString &topic, quint8 QoS, QWidget *widget) {
  auto subscription = this->subscription(topic);

  if (!subscription) {
    subscription = m_client->subscribe(topic, QoS);
    subscriptionList.append(subscription);

    if (!subscription)
      qDebug() << "Error, could not sub D:!";
  }

  if (!iodeviceWidgetSubscriptionMap.contains(widget->property("formId").toInt())) {
    QStringList subTopicList;
    subTopicList.append(topic);

    iodeviceWidgetSubscriptionMap.insert(widget->property("formId").toInt(), subTopicList);
    //createIODeviceWidgetSubscriptions(widget);
  } else {
    iodeviceWidgetSubscriptionMap.find(widget->property("formId").toInt())->append(topic);
  }
}

void MqttClient::addRecipeDataSubscription(quint8 QoS, QWidget *widget) {
  auto subscription = this->subscription(recipeDataTopic);

  if (!subscription) {
    subscription = m_client->subscribe(recipeDataTopic, QoS);
    subscriptionList.append(subscription);

    if (!subscription)
      qDebug() << "Error, could not sub D:!";
  }

  if (!recipeWidgetSubscriptionMap.contains(widget->property("formId").toInt())) {

    QStringList subTopicList;
    subTopicList.append(recipeDataTopic);

    recipeWidgetSubscriptionMap.insert(widget->property("formId").toInt(), subTopicList);
    createRecipeWidgetSubscriptions(widget);
  }
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
      qDebug() << QLatin1String(": State Change Conecting ... ");
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
  //TransformPayload parser;

//  if (QString::compare(topic.name(), proximityLiftTopic) == 0 ||
//      QString::compare(topic.name(), relayStatesTopic) == 0) {
//
//    QVector<IODevice *> iodeviceList;
//    iodeviceList = parser.parseIODevices(message);
//
//    //emit newIODeviceStates(message);
//  } else if (QString::compare(topic.name(), recipeDataTopic) == 0) {
//
//    //WeightSensor *weightSensor = parser.parseRecipeData(message);
//    //emit newDataForScale(message);
//  }

  const QString content = QDateTime::currentDateTime().toString()
      + QLatin1String(" Received Topic: ")
      + topic.name()
      + QLatin1String(" Message: ")
      + message
      + QLatin1Char('\n');
  qDebug() << content;
}

void MqttClient::createRecipeWidgetSubscriptions(QWidget *widget) {
//  auto recipeStatusInterface =
//      dynamic_cast<RecipeStatusInterface *>(widget);
//
//  connect(this, &MqttClient::newDataForScale,
//          recipeStatusInterface, &RecipeStatusInterface::onUpdateIODevice);
//}
//
//void MqttClient::createIODeviceWidgetSubscriptions(QWidget *widget) {
//  auto widgetDeviceStatusInterface =
//      dynamic_cast<IOWidgetStatusInterface *>(widget);
//
//  connect(this, &MqttClient::newIODeviceStates,
//          widgetDeviceStatusInterface, &IOWidgetStatusInterface::onUpdateIODevices);
}