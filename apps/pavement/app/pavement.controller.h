#ifndef CONTROLLER_PAVEMENTCONTROLLER_H_
#define CONTROLLER_PAVEMENTCONTROLLER_H_

#include <QObject>
#include <QtWidgets/QLayout>
#include <QtWidgets/QStackedWidget>

#include <appservice.iodevices/iodevice.appservice.h>
#include <appservice.broker/brokerappservice.h>

class PavementController : public QObject {
 Q_OBJECT

 public:
  explicit PavementController(QObject *parent = nullptr);
  void createStackedWidget(QLayout *layout);
  void updateCurrentWidget(int widgetNr);

 private:
  QStackedWidget *stackedWidget = nullptr;
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
};

#endif //CONTROLLER_PAVEMENTCONTROLLER_H_