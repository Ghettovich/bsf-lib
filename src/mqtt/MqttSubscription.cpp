#include "MqttSubscription.h"

MqttSubscription::MqttSubscription(QObject *parent)
    : QObject(parent)
{
    onUpdateStatus(m_sub->state());
    connect(m_sub, &QMqttSubscription::messageReceived, this, &MqttSubscription::onUpdateMessage);
    connect(m_sub, &QMqttSubscription::stateChanged, this, &MqttSubscription::onUpdateStatus);
    connect(m_sub, &QMqttSubscription::qosChanged, [this](quint8 qos) {
        qDebug() << (QString::number(qos));
    });
}
void MqttSubscription::onUpdateMessage(const QMqttMessage &msg)
{
    qDebug() << msg.payload();
}
void MqttSubscription::onUpdateStatus(QMqttSubscription::SubscriptionState state)
{
    switch (state) {
        case QMqttSubscription::Unsubscribed:
            qDebug() << (QLatin1String("Unsubscribed"));
            break;
        case QMqttSubscription::SubscriptionPending:
            qDebug() << (QLatin1String("Pending"));
            break;
        case QMqttSubscription::Subscribed:
            qDebug() << (QLatin1String("Subscribed"));
            break;
        case QMqttSubscription::Error:
            qDebug() << (QLatin1String("Error"));
            break;
        default:
            qDebug() << (QLatin1String("--Unknown--"));
            break;
    }
}
