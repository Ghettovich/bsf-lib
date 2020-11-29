#ifndef MQTTSUBSCRIPTION_H
#define MQTTSUBSCRIPTION_H

#include <QObject>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>

class MqttSubscription: public QObject
{
Q_OBJECT

public:
    explicit MqttSubscription(QObject *parent);

public slots:
    void onUpdateMessage(const QMqttMessage &msg);
    void onUpdateStatus(QMqttSubscription::SubscriptionState state);

private:
    QMqttSubscription *m_sub;
};


#endif //MQTTSUBSCRIPTION_H
