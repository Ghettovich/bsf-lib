#include "relay.button.h"

RelayButton::RelayButton(QWidget *_sensorWidget, QWidget *parent) :
    SensorWidget(_sensorWidget, parent) {
  relayButton = dynamic_cast<QPushButton*>(_sensorWidget);
  relayButton->setIcon(materialRegular.boltIcon(Qt::red));

  connect(relayButton, &QPushButton::clicked, this, &RelayButton::onClickToggleRelay);
}

void RelayButton::updateWidgetState(bool on) {
  if(on) {
    relayButton->setIcon(materialRegular.boltIcon(Qt::green));
  } else {
    relayButton->setIcon(materialRegular.boltIcon(Qt::red));
  }
}
void RelayButton::onClickToggleRelay() {
  qDebug() << "toggle relay with id: " << relayButton->property("deviceId").toInt();
  emit toggleRelay(relayButton->property("deviceId").toInt());
}
