#ifndef BSF_LIB_MQTTCLIENT_H
#define BSF_LIB_MQTTCLIENT_H

#include <QObject>
#include <QtMqtt/QMqttClient>

class MqttClient: public QObject
{

Q_OBJECT

public:
    explicit MqttClient(QObject *parent);
    void connectToHost();
    void publish(const QString &topic, const QString &message);
    QMqttSubscription *subscribe(const QString &topic);
    QMqttClient::ClientState getClientState() const;

public slots:
    void onBrokerDisconnected();
    void onStateChanged();
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

private:
    QMqttClient *m_client;

signals:
    void brokerConnected();
};


#endif //BSF_LIB_MQTTCLIENT_H
