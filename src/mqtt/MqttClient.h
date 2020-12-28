#ifndef BSF_LIB_MQTTCLIENT_H
#define BSF_LIB_MQTTCLIENT_H

#include <iodevice.h>
#include <relay.h>
#include <recipe.h>
#include <weightcensor.h>
#include <QObject>
#include <QtCore/QList>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>

class MqttClient : public QObject {

 Q_OBJECT

 public:
  explicit MqttClient(QObject *parent, const QString& host = "localhost");
  void connectToHost();
  void publishToggleRelay(IODevice *iodevice);
  void publishConfirmComponent(const Component &component);
  void publishTareScale(bool confirm, int calibrationWeight = 1000);
  void publishRecipe(const Recipe &recipe, const Component &component = Component(0));
  void addIODeviceSubscription(const QString &topic, quint8 QoS, QWidget *widget);
  void addRecipeDataSubscription(quint8 QoS, QWidget *widget);
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
  QMap<int, QStringList> iodeviceWidgetSubscriptionMap;
  QMap<int, QStringList> recipeWidgetSubscriptionMap;
  const QString toggleRelayTopic = "/toggle/relay";
  const QString configureRecipeTopic = "/config/recipe";
  const QString recipeDataTopic = "/recipe/data";
  const QString proximityLiftTopic = "/proximity/lift";
  const QString relayStatesTopic = "/relay/states";
  const QString tareScaleTopic = "/tare/scale";

  void createIODeviceWidgetSubscriptions(QWidget *widget);
  void createRecipeWidgetSubscriptions(QWidget *);

 signals:
  void brokerConnected();
  void newDataForScale(const WeightSensor *ioDevice);
  void newIODeviceStates(const QVector<IODevice *> &iodeviceList);
};

#endif //BSF_LIB_MQTTCLIENT_H
