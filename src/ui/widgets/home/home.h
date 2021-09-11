#ifndef BSF_LIB_SRC_UI_WIDGETS_HOME_HOME_H_
#define BSF_LIB_SRC_UI_WIDGETS_HOME_HOME_H_

#include <QWidget>
#include <appservice.iodevices/iodevice.appservice.h>

namespace Ui {
class Home;
}

class Home : public QWidget {
  Q_OBJECT

 public:
  explicit Home(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService,
                QWidget *parent = nullptr);
  virtual ~Home();

 public slots:
  void onUpdateProximities(int deviceId, bool status);
  void onUpdateRelays(int deviceId, bool status);

 private:
  Ui::Home *ui = nullptr;
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
};

#endif //BSF_LIB_SRC_UI_WIDGETS_HOME_HOME_H_
