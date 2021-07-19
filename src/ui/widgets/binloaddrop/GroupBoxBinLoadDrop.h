#ifndef BSF_LIB_GROUPBOXBINLOADDROP_H
#define BSF_LIB_GROUPBOXBINLOADDROP_H

#include <QtWidgets/QWidget>

#include <iodevice/iodevice.h>
#include <fonts/MaterialRegular.h>
#include <appservice.broker/BrokerAppService.h>

namespace Ui {
class GroupBoxBinLoadDrop;
}

class GroupBoxBinLoadDrop : public QWidget {
 Q_OBJECT

 public:
  explicit GroupBoxBinLoadDrop(std::shared_ptr<appservice::BrokerAppService> &brokerAppService,
                               QWidget *parent = nullptr);
  virtual ~GroupBoxBinLoadDrop();
  void init();

 public slots:
  void onUpdateIODevices(const QVector<IODevice *> &devices);

 private:
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
  Ui::GroupBoxBinLoadDrop *ui = nullptr;
  MaterialRegular materialRegular;

  std::unique_ptr<IODevice> relayBinLoad;
  std::unique_ptr<IODevice> relayBinDrop;
  std::unique_ptr<IODevice> proximityBinDrop;

  void setProximityBinDropLabelStatus();
  void setBinLoadButtonState();
  void setBinDropButtonState();
  void onChangeProximity(IODevice *detectionSensor);
  void onToggledBinLoadRelay(IODevice *relay);
  void onToggledBinDropRelay(IODevice *relay);

 private slots:
  void onClickPushButtonBinLoad();
  void onClickPushButtonBinDrop();

// signals:
//  void toggledRelay(IODevice *relay);
//  void proximityStateChange(IODevice *detectionSensor);
};

#endif //BSF_LIB_GROUPBOXBINLOADDROP_H
