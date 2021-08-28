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

 public slots:
  void onClickToggleRelay();

 signals:
  void toggleRelay(int id);
};

#endif //BSF_LIB_SRC_UI_BUTTONS_RELAY_RELAY_BUTTON_H_
