#ifndef BSF_BROKERSERVICE_H_
#define BSF_BROKERSERVICE_H_

#include <QObject>
#include <broker/client/MqttClient.h>

namespace service {
class BrokerService;
}

class service::BrokerService : public QObject {
 Q_OBJECT

 public:
  explicit BrokerService(QObject *parent = nullptr);
  void connectToHost();
  void addSubscription(const QString &topic, quint8 qos = 1);
  void toggleRelay(int relayId);
  void tareScale(int scaleId);
  void calibrateScale(int scaleId, bool confirm, double weight);
  void configureRecipe(int recipeId, int componentId, int targetWeight);

 private:
  const QString toggleRelayTopic = "toggle/relay";
  const QString tareScaleTopic = "scale/tare";
  const QString calibrateScaleTopic = "scale/calibrate";
  const QString configureRecipeTopic = "/config/recipe";

  std::unique_ptr<MqttClient> m_client;
  QString getHost(QObject *parent);

 signals:
  void connectedToHost();
  void newMessageForTopic(const QByteArray &message, const QString &topic);

};

#endif //BSF_BROKERSERVICE_H_
