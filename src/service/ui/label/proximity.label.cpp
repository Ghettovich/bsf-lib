#include "proximity.label.h"

ProximityLabel::ProximityLabel(QWidget *sensorWidget, QWidget *parent) :
    SensorWidget(sensorWidget, parent) {
  proximityLabel = dynamic_cast<QLabel *>(sensorWidget);
  proximityLabel->setPixmap(materialRegular.visibilityOffIcon(Qt::darkGray).pixmap(pxSize, pxSize));
}

void ProximityLabel::updateWidgetState(bool on) {
  if (on) {
    proximityLabel->setPixmap(materialRegular.visibilityIcon(Qt::lightGray).pixmap(pxSize, pxSize));
  } else {
    proximityLabel->setPixmap(materialRegular.visibilityOffIcon(Qt::darkGray).pixmap(pxSize, pxSize));
  }
}
