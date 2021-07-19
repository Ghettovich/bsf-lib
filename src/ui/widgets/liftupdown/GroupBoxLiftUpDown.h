#ifndef BSF_LIB_GROUPBOXLIFTUPDOWN_H
#define BSF_LIB_GROUPBOXLIFTUPDOWN_H

#include <QtWidgets/QWidget>

#include <iodevice/iodevice.h>
#include <fonts/MaterialRegular.h>
#include <appservice.broker/BrokerAppService.h>

namespace Ui {
class GroupBoxLiftUpDown;
}

class GroupBoxLiftUpDown : public QWidget {
 Q_OBJECT

 public:
  explicit GroupBoxLiftUpDown(std::shared_ptr<appservice::BrokerAppService> &brokerAppService,
                              QWidget *parent = nullptr);
  virtual ~GroupBoxLiftUpDown();
  void init();

 public slots:
  void onUpdateIODevices(const QVector<IODevice *> &devices);

 private:
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
  Ui::GroupBoxLiftUpDown *ui = nullptr;
  MaterialRegular materialRegular;

  std::unique_ptr<IODevice> relayBinLiftUp;
  std::unique_ptr<IODevice> relayBinLiftDown;
  std::unique_ptr<IODevice> proximityBinLoad;

  void setProximityBinLoadStatusLabel();
  void setLiftUpButtonState();
  void setLiftDownButtonState();

  void onChangeProximity(IODevice *detectionSensor);
  void onToggledLiftUpRelay(IODevice *relay);
  void onToggledLiftDownRelay(IODevice *relay);

 private slots:
  void onClickPushButtonLiftDown();
  void onClickPushButtonLiftUp();

// signals:
//  void toggledRelay(IODevice *relay);
//  void proximityStateChange(IODevice *detectionSensor);
};

#endif //BSF_LIB_GROUPBOXLIFTUPDOWN_H
