#include "MqttClient.h"
#include <QString>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
MqttClient::MqttClient(QObject *parent)
    : QObject(parent)
{
    m_client = new QMqttClient(this);
    m_client->setHostname("localhost");
    m_client->setPort(1883);

    connect(m_client, &QMqttClient::stateChanged, this, &MqttClient::onStateChanged);
    connect(m_client, &QMqttClient::disconnected, this, &MqttClient::onBrokerDisconnected);
    connect(m_client, &QMqttClient::messageReceived, this, &MqttClient::onMessageReceived);

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]()
    {
        const QString content = QDateTime::currentDateTime().toString()
            + QLatin1String(" PingResponse")
            + QLatin1Char('\n');
        qDebug() << content;
    });
}
QMqttClient::ClientState MqttClient::getClientState() const
{
    return m_client->state();
}
void MqttClient::connectToHost()
{
    if(m_client->state() == QMqttClient::Disconnected &&
        m_client->state() != QMqttClient::Connecting) {
        m_client->connectToHost();
    }
}
void MqttClient::publish(const QString &topicName, const QString &message)
{
    QMqttTopicName topic(topicName);

    if (m_client->publish(topic,
                          message.toLocal8Bit(),
                          0,
                          true) == -1) {
        qDebug() << "Failed to publish D:!";
    }
}
void MqttClient::publish(const QString &topic, const QJsonObject &jsonObject)
{
    doc = QJsonDocument(jsonObject);

    if (m_client->publish(topic,
                          doc.toJson(),
                          1,
                          true) == -1) {
        qDebug() << "Failed to publish D:!";
    }
}
QMqttSubscription *MqttClient::subscribe(const QString &topic)
{
    auto subscription = m_client->subscribe(topic, 1);
    if (!subscription) {
        qDebug() << "Error, could not sub D:!";
        return nullptr;
    }
    return subscription;
}
void MqttClient::onBrokerDisconnected()
{
    qDebug() << "Broker disconnected!";
}
void MqttClient::onStateChanged()
{
    qDebug() << "on state changed triggered...";
    switch (m_client->state()) {

        case QMqttClient::Disconnected: {
            const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(": State Change Disconnected ")
                + QString::number(m_client->state())
                + QLatin1Char('\n');
            qDebug() << content;
            break;
        }
        case QMqttClient::Connecting: {
            const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(": State Change Conecting ... ")
                + QString::number(m_client->state())
                + QLatin1Char('\n');
            qDebug() << content;
            break;
        }
        case QMqttClient::Connected: {
            emit brokerConnected();
            const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(": !!! State Change Connected! ")
                + QString::number(m_client->state())
                + QLatin1Char('\n');
            qDebug() << content;
            break;
        }
    }
}
void MqttClient::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(" Received Topic: ")
        + topic.name()
        + QLatin1String(" Message: ")
        + message
        + QLatin1Char('\n');
    qDebug() << content;
}
