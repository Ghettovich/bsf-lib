#ifndef BSF_LIB_SRC_SERVICE_UI_SCALE_SCALE_LCDNUMBER_H_
#define BSF_LIB_SRC_SERVICE_UI_SCALE_SCALE_LCDNUMBER_H_

#include <QLCDNumber>
#include <ui/interfaces/sensor.widget.h>

class ScaleLcdNumber : public SensorWidget {
  Q_INTERFACES(SensorWidget)

 public:
  explicit ScaleLcdNumber(QWidget *sensorWidget, QWidget *parent);
  void updateWidgetState(bool on) override;
  void setScaleWeight(int weight);

 private:
  QLCDNumber *lcdNumber;
};

#endif //BSF_LIB_SRC_SERVICE_UI_SCALE_SCALE_LCDNUMBER_H_
