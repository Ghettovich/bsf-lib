#ifndef RELAYTREEWIDGET_H
#define RELAYTREEWIDGET_H

#include <QtWidgets/QWidget>

#include <iodevice/iodevice.h>
#include <appservice.iodevices/iodevice.appservice.h>

namespace Ui {
class RelayTreeWidget;
}

class RelayTreeWidget : public QWidget {
 Q_OBJECT

 public:
  explicit RelayTreeWidget(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService);

 private slots:
  void onUpdateIODevices(const QList<IODevice *> &iodeviceList);

 private:
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  Ui::RelayTreeWidget *ui = nullptr;

  void initForm();
};

#endif //RELAYTREEWIDGET_H
