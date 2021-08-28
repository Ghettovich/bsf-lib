#include "relay.button.h"

RelayButton::RelayButton(QWidget *parent) : DevicePushButton(parent) {
  setIcon(materialRegular.boltIcon(Qt::red));

  connect(this, &RelayButton::clicked, this, &RelayButton::onClickToggleRelay);
}

void RelayButton::updateButtonState(bool on) {
  if(on) {
    setIcon(materialRegular.boltIcon(Qt::green));
  } else {
    setIcon(materialRegular.boltIcon(Qt::red));
  }
}
void RelayButton::onClickToggleRelay() {
  emit toggleRelay(property("relay").toInt());
}
