#include "scale.lcdnumber.h"

ScaleLcdNumber::ScaleLcdNumber(QWidget *sensorWidget, QWidget *parent) :
    SensorWidget(sensorWidget, parent) {
  lcdNumber = dynamic_cast<QLCDNumber *>(sensorWidget);
  lcdNumber->setEnabled(false);
}
void ScaleLcdNumber::updateWidgetState(bool on) {
  lcdNumber->setEnabled(on);
}
void ScaleLcdNumber::setScaleWeight(int weight) {
  lcdNumber->display(weight);
}
