#ifndef BSF_LIB_SRC_UI_INTERFACES_DEVICE_WIDGET_INTERFACE_H_
#define BSF_LIB_SRC_UI_INTERFACES_DEVICE_WIDGET_INTERFACE_H_

#include <QtPlugin>
#include <QtWidgets/QWidget>
#include <ui/fonts/MaterialRegular.h>

class SensorWidget : public QWidget {
 Q_OBJECT

 public:
  SensorWidget(QWidget *sensorWidget, QWidget *parent);
  virtual void updateWidgetState(bool on) = 0;

 protected:
  QWidget *sensorWidget = nullptr;
  MaterialRegular materialRegular;
};

#define SensorWidget_iid "SensorWidget"

Q_DECLARE_INTERFACE(SensorWidget, SensorWidget_iid)

#endif //BSF_LIB_SRC_UI_INTERFACES_DEVICE_WIDGET_INTERFACE_H_
