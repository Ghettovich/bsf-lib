#ifndef BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_
#define BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_

#include <QWidget>
#include <appservice.iodevices/iodevice.appservice.h>
#include <appservice.statemachine/statemachine.appservice.h>

namespace Ui {
class Experimental;
}

class Experimental : public QWidget {
 Q_OBJECT

 public:
  explicit Experimental(std::shared_ptr<appservice::IODeviceAppService> &deviceAppService,
                        std::shared_ptr<appservice::StateMachineAppService> &statemachineAppService,
                        QWidget *parent = nullptr);
  virtual ~Experimental();
  QList<QWidget *> deviceWidgets();

 private:
  Ui::Experimental *ui = nullptr;
  std::shared_ptr<appservice::IODeviceAppService> deviceAppService;
  std::shared_ptr<appservice::StateMachineAppService> statemachineAppService;
};

#endif //BSF_LIB_SRC_UI_WIDGETS_EXPERIMENTAL_EXPERIMENTAL_H_
