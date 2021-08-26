#include "device.pushbutton.h"

DevicePushButton::DevicePushButton(QWidget *parent) : QPushButton(parent) {
}
void DevicePushButton::setDeviceId(int id) {
  setProperty("deviceId", id);
  qDebug() << "button device id = " << property("deviceId").toInt();
}
