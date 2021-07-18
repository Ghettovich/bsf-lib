#ifndef RELAYTREEWIDGET_H
#define RELAYTREEWIDGET_H

#include <QtWidgets/QWidget>

#include <iodevice.h>
#include <fonts/MaterialRegular.h>
#include <appservice.broker/BrokerAppService.h>

namespace Ui {
class RelayTreeWidget;
}

class RelayTreeWidget : public QWidget {
 Q_OBJECT

 public:
  explicit RelayTreeWidget(std::shared_ptr<appservice::BrokerAppService> &brokerAppService);

 private slots:
  void onUpdateIODevices(const QVector<IODevice *> &iodeviceList);

 private:
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
  Ui::RelayTreeWidget *ui = nullptr;
  MaterialRegular materialRegular;

  void initForm();
};

#endif //RELAYTREEWIDGET_H
