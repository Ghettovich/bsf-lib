#include "proximity.label.h"

ProximityLabel::ProximityLabel(QWidget *parent) : QLabel(parent) {
  setPixmap(materialRegular.visibilityOffIcon(Qt::darkGray).pixmap(48, 48));
}
void ProximityLabel::updateProximityStatus(bool on) {
  if (on) {
    setPixmap(materialRegular.visibilityIcon(Qt::lightGray).pixmap(48, 48));
  } else {
    setPixmap(materialRegular.visibilityOffIcon(Qt::darkGray).pixmap(48, 48));
  }
}
