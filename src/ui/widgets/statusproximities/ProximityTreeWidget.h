#ifndef PROXIMITYTREEWIDGET_H
#define PROXIMITYTREEWIDGET_H

#include <QtWidgets/QWidget>

#include <iodevice.h>
#include <fonts/MaterialRegular.h>
#include <appservice.broker/BrokerAppService.h>

namespace Ui {
class ProximityTreeWidget;
}

class ProximityTreeWidget : public QWidget {
 Q_OBJECT

 public:
  explicit ProximityTreeWidget(std::shared_ptr<appservice::BrokerAppService> &brokerAppService);

 public slots:
  void onUpdateIODevices(const QVector<IODevice *> &iodeviceList);

 private:
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
  Ui::ProximityTreeWidget *ui = nullptr;
  MaterialRegular materialRegular;

  void initForm();
};

#endif //PROXIMITYTREEWIDGET_H
