#ifndef BSF_LIB_SRC_UI_BUTTONS_DEVICE_PUSHBUTTON_H_
#define BSF_LIB_SRC_UI_BUTTONS_DEVICE_PUSHBUTTON_H_

#include <QtPlugin>
#include <QPushButton>
#include <fonts/MaterialRegular.h>

class DevicePushButton : public QPushButton {
 Q_OBJECT

 public:
  explicit DevicePushButton(QWidget *parent = nullptr);
  void setDeviceId(int id);
  virtual void updateButtonState(bool on) = 0;

 protected:
  MaterialRegular materialRegular;
};

#define DevicePushButton_iid "DevicePushButton"

Q_DECLARE_INTERFACE(DevicePushButton, DevicePushButton_iid)

#endif //BSF_LIB_SRC_UI_BUTTONS_DEVICE_PUSHBUTTON_H_
