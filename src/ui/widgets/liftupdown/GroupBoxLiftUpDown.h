#ifndef BSF_LIB_GROUPBOXLIFTUPDOWN_H
#define BSF_LIB_GROUPBOXLIFTUPDOWN_H

namespace Ui {
class GroupBoxLiftUpDown;
}

#include <MqttClient.h>
#include <iodevice.h>
#include <relay.h>
#include <detectionsensor.h>
#include <fonts/MaterialRegular.h>
#include <ui/widgets/interfaces/IOWidgetStatusInterface.h>
#include <QtWidgets/QWidget>

class GroupBoxLiftUpDown : public IOWidgetStatusInterface {
 Q_OBJECT
  Q_INTERFACES(IOWidgetStatusInterface)

 public:
  explicit GroupBoxLiftUpDown(MqttClient *_m_client);
  virtual ~GroupBoxLiftUpDown();
  void init();

 public slots:
  void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) override;
  void onChangeProximity(IODevice *detectionSensor);
  void onToggledLiftUpRelay(IODevice *relay);
  void onToggledLiftDownRelay(IODevice *relay);

 private:
  Ui::GroupBoxLiftUpDown *ui = nullptr;
  MqttClient *m_client = nullptr;
  MaterialRegular materialRegular;
  IODevice *relayBinLiftUp;
  IODevice *relayBinLiftDown;
  IODevice *proximityBinLoad;

  void setProximityBinLoadStatusLabel();
  void setLiftUpButtonState();
  void setLiftDownButtonState();

 private slots:
  void onClickPushButtonLiftDown();
  void onClickPushButtonLiftUp();

  signals:
  void toggledRelay(IODevice *relay);
  void proximityStateChange(IODevice *detectionSensor);
};

#endif //BSF_LIB_GROUPBOXLIFTUPDOWN_H
