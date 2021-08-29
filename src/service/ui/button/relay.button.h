#ifndef BSF_LIB_SRC_UI_BUTTONS_RELAY_RELAY_BUTTON_H_
#define BSF_LIB_SRC_UI_BUTTONS_RELAY_RELAY_BUTTON_H_

#include <QtPlugin>
#include <QPushButton>
#include <ui/interfaces/sensor.widget.h>

class RelayButton : public SensorWidget {
  Q_OBJECT
  Q_INTERFACES(SensorWidget)

 public:
  RelayButton(QWidget *_sensorWidget, QWidget *parent);
  void updateWidgetState(bool on) override;

 public slots:
  void onClickToggleRelay();

 private:
  QPushButton *relayButton = nullptr;

 signals:
  void toggleRelay(int id);
};

#endif //BSF_LIB_SRC_UI_BUTTONS_RELAY_RELAY_BUTTON_H_
