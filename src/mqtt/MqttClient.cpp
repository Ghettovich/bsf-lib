#include "MqttClient.h"
#include <BsfWidgetEnum.h>
#include <transformpayload.h>
#include <QString>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <widgets/devicestatus/IOWidgetStatusInterface.h>

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
void MqttClient::publishToggleRelay(IODevice *iodevice)
{
    quint8 QoS = 1;
    QJsonObject jsonPayload;
    jsonPayload["toggle"] = iodevice->getId();

    doc = QJsonDocument(jsonPayload);

    if (m_client->publish(toggleRelayTopic,
                          doc.toJson(),
                          QoS,
                          false) == -1) {

    }
}
void MqttClient::addIODeviceSubscription(const QString &topic, quint8 QoS, QWidget *widget)
{
    auto subscription = this->subscription(topic);

    if (!subscription) {
        subscription = m_client->subscribe(topic, QoS);
        subscriptionList.append(subscription);

        if (!subscription)
            qDebug() << "Error, could not sub D:!";
    }

    if(!widgetSubscriptionMap.contains(widget->property("formId").toInt())) {
        createIODeviceWidgetSubscriptions(widget);
    }
}
QMqttSubscription *MqttClient::subscription(const QString &topic)
{
    for (const auto sub : subscriptionList) {
        if(sub->topic().match(topic)) {
            return sub;
            qDebug() << "Found matching sub";
        }
    }

    return nullptr;
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
                + QLatin1String(": State Change Connected! ")
                + QString::number(m_client->state())
                + QLatin1Char('\n');
            qDebug() << content;
            break;
        }
    }
}
void MqttClient::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    QVector<IODevice *> iodeviceList;
    parseMessagePayload(topic.name(), message, iodeviceList);

    if(!iodeviceList.empty()) {
        emit newIODeviceStates(iodeviceList);
    }

//    const QString content = QDateTime::currentDateTime().toString()
//        + QLatin1String(" Received Topic: ")
//        + topic.name()
//        + QLatin1String(" Message: ")
//        + message
//        + QLatin1Char('\n');
//    qDebug() << content;
}
void MqttClient::createIODeviceWidgetSubscriptions(QWidget *widget)
{
    IOWidgetStatusInterface *widgetDeviceStatusInterface =
        qobject_cast<IOWidgetStatusInterface*>(widget);

    connect(this, &MqttClient::newIODeviceStates,
            widgetDeviceStatusInterface, &IOWidgetStatusInterface::onUpdateIODevices);
}
void MqttClient::parseMessagePayload(const QMqttTopicName &topic, const QByteArray &payload, QVector<IODevice *> &iodeviceList)
{
    TransformPayload parser;

    if(QString::compare(topic.name(), "/proximity/lift") == 0) {
        iodeviceList = parser.parseProximitySensors(payload);
    } else if(QString::compare(topic.name(), "/relay/states") == 0) {
        iodeviceList = parser.parseRelayStates(payload);
    }
}
