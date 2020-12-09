#include "MqttClient.h"
#include <BsfWidgetEnum.h>
#include <transformpayload.h>
#include <QString>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <ui/widgets/liftupdown/GroupBoxLiftUpDown.h>
#include <ui/widgets/binloaddrop/GroupBoxBinLoadDrop.h>

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
void MqttClient::publish(const QString &topic, const QJsonObject &jsonObject)
{
    doc = QJsonDocument(jsonObject);

    if (m_client->publish(topic,
                          doc.toJson(),
                          1,
                          false) == -1) {
        qDebug() << "Failed to publish D:!";
    }
}
void MqttClient::addSubscription(const QString &topic, quint8 QoS)
{
    auto subscription = m_client->subscribe(topic, QoS);
    if (!subscription) {
        qDebug() << "Error, could not sub D:!";
    } else {
        subscriptionList.append(subscription);
    }
}
void MqttClient::addSubscription(const QString &topic, quint8 QoS, QWidget *widget)
{
    auto subscription = this->subscription(topic);

    if (!subscription) {
        subscription = m_client->subscribe(topic, QoS);
        subscriptionList.append(subscription);

        if (!subscription)
            qDebug() << "Error, could not sub D:!";
    }

    if(widgetSubscriptionMap.contains(widget->property("formId").toInt())) {
        widgetSubscriptionMap.find(widget->property("formId").toInt()).value().append(topic);
    } else {
        QStringList subStringList;
        subStringList.append(topic);

        // ID of widget is not found in hash map, insert it and add to list
        widgetSubscriptionMap.insert(widget->property("formId").toInt(), subStringList);
        widgetList.append(widget);
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
    TransformPayload parser;
    QVector<IODevice *> iodeviceList;

//    parseMessagePayload(topic.name(), message, iodeviceList);
//
//    if(!iodeviceList.empty()) {
//        updateSubscribedWidgets(topic.name(), iodeviceList);
//    }

    if(QString::compare(topic.name(), "/proximity/lift") ||
        QString::compare(topic.name(), "/relay/states")) {

        iodeviceList = parser.parseProximitySensors(message);
        QMapIterator<int, QStringList> i(widgetSubscriptionMap);

        while (i.hasNext()) {
            i.next();

            if(i.value().contains(topic.name())) {

                for(const auto widget : widgetList) {

                    switch (widget->property("formId").toInt()) {
                        case WIDGET_TYPES::GROUPBOX_LIFT_UP_DOWN: {
                            auto formGroupBox = dynamic_cast<GroupBoxLiftUpDown*>(widget);
                            formGroupBox->onUpdateIODevices(iodeviceList);
                            break;
                        }
                        case WIDGET_TYPES::GROUPBOX_BIN_LOAD_DROP: {
                            auto formGroupBox = dynamic_cast<GroupBoxBinLoadDrop*>(widget);
                            formGroupBox->onUpdateIODevices(iodeviceList);
                            break;
                        }
                    }
                }
            }
        }
    }
//
    const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(" Received Topic: ")
        + topic.name()
        + QLatin1String(" Message: ")
        + message
        + QLatin1Char('\n');
    qDebug() << content;
}
void MqttClient::updateSubscribedWidgets(const QMqttTopicName &topic, const QVector<IODevice *> &iodeviceList)
{
    QMapIterator<int, QStringList> i(widgetSubscriptionMap);

    while (i.hasNext()) {
        i.next();

        if(i.value().contains(topic.name())) {

            for(const auto widget : widgetList) {

                switch (widget->property("formId").toInt()) {
                    case WIDGET_TYPES::GROUPBOX_LIFT_UP_DOWN: {
                        auto formGroupBox = dynamic_cast<GroupBoxLiftUpDown*>(widget);
                        formGroupBox->onUpdateIODevices(iodeviceList);
                        break;
                    }
                    case WIDGET_TYPES::GROUPBOX_BIN_LOAD_DROP: {
                        auto formGroupBox = dynamic_cast<GroupBoxBinLoadDrop*>(widget);
                        formGroupBox->onUpdateIODevices(iodeviceList);
                        break;
                    }
                }
            }
        }
    }
}
void MqttClient::parseMessagePayload(const QMqttTopicName &topic, const QByteArray &payload, QVector<IODevice *> &iodeviceList)
{
    TransformPayload parser;
    qDebug() << topic;

    if(QString::compare(topic.name(), "/proximity/lift")) {
        iodeviceList = parser.parseProximitySensors(payload);
    } else if(QString::compare(topic.name(), "/relay/states")) {
        iodeviceList = parser.parseRelayStates(payload);
    }
}
