#ifndef OPERATORMQTTCLIENT_H
#define OPERATORMQTTCLIENT_H

namespace Ui {
class OperatorMqttClient;
}

#include <QObject>
#include <QtWidgets/QWidget>
#include <QtMqtt/QtMqtt>

class OperatorMqttClient : public QWidget {

 Q_OBJECT

 public:
  OperatorMqttClient(QWidget *parent, const Qt::WindowFlags &f);
  virtual ~OperatorMqttClient();

 public slots:
  void onUpdateLogStateChange();
  void onBrokerDisconnected();

 private:
  Ui::OperatorMqttClient *ui = nullptr;
  QMqttClient *m_client;

 private slots:
  void onPushButtonConnectClicked();
  void onPushButtonSubscribeClicked();
  void onPushButtonPublishClicked();
};

#endif //OPERATORMQTTCLIENT_H
