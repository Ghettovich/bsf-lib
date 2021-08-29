#ifndef BSF_LIB_SRC_SERVICE_UI_PROXIMITYLABEL_H_
#define BSF_LIB_SRC_SERVICE_UI_PROXIMITYLABEL_H_

#include <QLabel>
#include <ui/interfaces/sensor.widget.h>

class ProximityLabel : public SensorWidget {
  Q_INTERFACES(SensorWidget)

 public:
  explicit ProximityLabel(QWidget *sensorWidget, QWidget *parent);
  void updateWidgetState(bool on) override;

 private:
  const int pxSize = 48;
  QLabel *proximityLabel;
};

#endif //BSF_LIB_SRC_SERVICE_UI_PROXIMITYLABEL_H_
