#ifndef BSF_LIB_SRC_UI_BUTTONS_RELAY_RELAY_BUTTON_H_
#define BSF_LIB_SRC_UI_BUTTONS_RELAY_RELAY_BUTTON_H_

#include <QtPlugin>
#include <buttons/device.pushbutton.h>

class RelayButton : public DevicePushButton {
  Q_OBJECT
  Q_INTERFACES(DevicePushButton)

 public:
  explicit RelayButton(QWidget *parent);
  void updateButtonState(bool on) override;
};

#endif //BSF_LIB_SRC_UI_BUTTONS_RELAY_RELAY_BUTTON_H_
