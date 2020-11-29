#ifndef BSF_LIB_MQTTCLIENT_H
#define BSF_LIB_MQTTCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtMqtt/QMqttClient>

class MqttClient: public QObject
{
Q_OBJECT

public:
    explicit MqttClient(QObject *parent);
    void publish(const QString &topic);
    void subscribe(const QString &topic);

public slots:
    void onUpdateLogStateChange();
    void onBrokerDisconnected();

private:
    QMqttClient *m_client;
    QStringList logStateChanges;
};


#endif //BSF_LIB_MQTTCLIENT_H
