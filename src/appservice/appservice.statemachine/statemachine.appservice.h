#ifndef BSF_STATEMACHINEAPPSERVICE_H_
#define BSF_STATEMACHINEAPPSERVICE_H_

#include <QObject>
#include <QState>
#include <QFinalState>
#include <QStateMachine>
#include <iodevice/iodeviceservice.h>

namespace appservice {
class StateMachineAppService;
}

class appservice::StateMachineAppService : public QObject {
 Q_OBJECT

 public:
  explicit StateMachineAppService(std::shared_ptr<service::BrokerService> &brokerService,
                                  std::shared_ptr<IODeviceService> &deviceService,
                                  QObject *parent = nullptr);

 void sendLiftToLoad();

 public slots:
  void onIODeviceChange(int deviceId, bool status);
  void onStartedStateMachine();
  void onFinishedStateMachine();

 private:
  QTimer liftMovingTimeOut;
  QStateMachine *qmachine = new QStateMachine;
  std::shared_ptr<service::BrokerService> brokerService;
  std::shared_ptr<IODeviceService> deviceService;

  void defineLiftTransitionStates();

 private slots:
  void toggleLiftDownRelay();
  void startLiftTimeOut();

};

#endif //BSF_STATEMACHINEAPPSERVICE_H_
