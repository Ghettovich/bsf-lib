#ifndef BSF_LIB_MQTTCLIENT_H
#define BSF_LIB_MQTTCLIENT_H

#include <iodevice.h>
#include <QObject>
#include <QtCore/QList>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>

class MqttClient: public QObject
{

Q_OBJECT

public:
    explicit MqttClient(QObject *parent);
    void connectToHost();
    void publish(const QString &topic, const QJsonObject &jsonObject);
    void addSubscription(const QString &topic, quint8 QoS);
    void addIODeviceSubscription(const QString &topic, quint8 QoS, QWidget *widget);
    QMqttSubscription *subscribe(const QString &topic);
    QMqttSubscription *subscription(const QString &topic);
    QMqttClient::ClientState getClientState() const;

public slots:
    void onBrokerDisconnected();
    void onStateChanged();
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

private:
    QMqttClient *m_client;
    QJsonDocument doc;
    QList<QMqttSubscription *> subscriptionList;
    QMap<int, QStringList> widgetSubscriptionMap;

    void createIODeviceWidgetSubscriptions(QWidget *widget);
    void parseMessagePayload(const QMqttTopicName &topic, const QByteArray &payload, QVector<IODevice *> &iodeviceList);

signals:
    void brokerConnected();
    void newIODeviceStates(const QVector<IODevice *> &iodeviceList);
    //void newRelayStates(const QVector<IODevice *> &iodeviceList);
};


#endif //BSF_LIB_MQTTCLIENT_H
