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


    connect(m_client, &QMqttClient::stateChanged, this, &MqttClient::onUpdateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MqttClient::onBrokerDisconnected);

    connect(m_client,
            &QMqttClient::messageReceived,
            this,
            [this](const QByteArray &message, const QMqttTopicName &topic)
            {
                const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" Received Topic: ")
                    + topic.name()
                    + QLatin1String(" Message: ")
                    + message
                    + QLatin1Char('\n');
                qDebug() << content;
            });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]()
    {
        const QString content = QDateTime::currentDateTime().toString()
            + QLatin1String(" PingResponse")
            + QLatin1Char('\n');
        qDebug() << content;
    });
}
void MqttClient::publish(const QString &topicName)
{
    QMqttTopicName topic(topicName);

    if (m_client->publish(topic,
                          "{\"relay\":30}",
                          0,
                          true) == -1) {
        qDebug() << "Failed to publish D:!";
    }
}
void MqttClient::subscribe(const QString &topic)
{
    auto subscription = m_client->subscribe(topic, 0);
    if (!subscription) {
        qDebug() << "Error, could not sub!";
        return;
    }
//    auto subWindow = new SubscriptionWindow(subscription);
//    subWindow->setWindowTitle(subscription->topic().filter());
//    subWindow->show();
}
void MqttClient::onUpdateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(": State Change")
        + QString::number(m_client->state())
        + QLatin1Char('\n');
    qDebug() << content;
}
void MqttClient::onBrokerDisconnected()
{
    qDebug() << "Broker disconnected!";
}
