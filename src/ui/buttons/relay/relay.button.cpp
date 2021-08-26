#include "relay.button.h"

RelayButton::RelayButton(QWidget *parent) : DevicePushButton(parent) {
  setIcon(materialRegular.boltIcon(Qt::red));
}

void RelayButton::updateButtonState(bool on) {
  if(on) {
    setIcon(materialRegular.boltIcon(Qt::green));
  } else {
    setIcon(materialRegular.boltIcon(Qt::red));
  }
}
