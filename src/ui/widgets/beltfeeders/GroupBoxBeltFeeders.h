#ifndef BSF_LIB_GROUPBOXBELTFEEDERS_H
#define BSF_LIB_GROUPBOXBELTFEEDERS_H

namespace Ui {
class GroupBoxBeltFeeders;
}

#include <QtWidgets/QWidget>

#include <iodevice.h>
#include <fonts/MaterialRegular.h>
#include <appservice.broker/BrokerAppService.h>

class GroupBoxBeltFeeders : public QWidget {
 Q_OBJECT

 public:
  explicit GroupBoxBeltFeeders(std::shared_ptr<appservice::BrokerAppService> &brokerAppService,
                               QWidget *parent = nullptr);

 public slots:
  void onUpdateIODevices(const QVector<IODevice *> &devices);

 private:
  std::shared_ptr<appservice::BrokerAppService> brokerAppService;
  Ui::GroupBoxBeltFeeders *ui = nullptr;
  MaterialRegular materialRegular;

  std::unique_ptr<IODevice> relayBeltForward;
  std::unique_ptr<IODevice> relayBeltReverse;
  std::unique_ptr<IODevice> relayFeeder1Foward;
  std::unique_ptr<IODevice> relayFeeder1Reverse;
  std::unique_ptr<IODevice> relayFeeder2Foward;
  std::unique_ptr<IODevice> relayFeeder2Reverse;

  void init();
  void setBeltForwardButtonState();
  void setBeltReverseButtonState();
  void setFeeder1ForwardButtonState();
  void setFeeder1ReverseButtonState();
  void setFeeder2ForwardButtonState();
  void setFeeder2ReverseButtonState();

 private slots:
  void onClickPushButtonBeltForward();
  void onClickPushButtonBeltReverse();
  void onClickPushButtonFeeder1Forward();
  void onClickPushButtonFeeder1Reverse();
  void onClickPushButtonFeeder2Forward();
  void onClickPushButtonFeeder2Reverse();
};

#endif //BSF_LIB_GROUPBOXBELTFEEDERS_H
