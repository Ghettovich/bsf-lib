#ifndef BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_
#define BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_

#include <QWidget>
#include <fonts/MaterialRegular.h>
#include <appservice.iodevices/iodevice.appservice.h>

namespace Ui {
class Experimental;
}

class Experimental : public QWidget {
 Q_OBJECT

 public:
  explicit Experimental(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService,
                        QWidget *parent = nullptr);
  virtual ~Experimental();
  QList<QWidget *> deviceWidgets();

 public slots:
  void onIODeviceStateChanged(int deviceId, bool on);

 private:
  Ui::Experimental *ui = nullptr;
  MaterialRegular materialRegular;

  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
};

#endif //BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_
