#ifndef PROXIMITYTREEWIDGET_H
#define PROXIMITYTREEWIDGET_H

#include <QtWidgets/QWidget>

#include <iodevice/iodevice.h>
#include <appservice.iodevices/iodevice.appservice.h>

namespace Ui {
class ProximityTreeWidget;
}

class ProximityTreeWidget : public QWidget {
 Q_OBJECT

 public:
  explicit ProximityTreeWidget(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService);

 public slots:
  void onUpdateIODevices(const QList<IODevice *> &iodeviceList);

 private:
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  Ui::ProximityTreeWidget *ui = nullptr;

  void initForm();
};

#endif //PROXIMITYTREEWIDGET_H
