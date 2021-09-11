#ifndef BSF_STATEMACHINEAPPSERVICE_H_
#define BSF_STATEMACHINEAPPSERVICE_H_

#include <QObject>
#include <QState>
#include <QFinalState>
#include <QStateMachine>
#include <iodevice/iodeviceservice.h>
#include <statemachine/machine.service.h>

namespace appservice {
class StateMachineAppService;
}

class appservice::StateMachineAppService : public QObject {
 Q_OBJECT

 public:
  explicit StateMachineAppService(std::shared_ptr<service::BrokerService> &brokerService,
                                  std::shared_ptr<IODeviceService> &deviceService,
                                  std::shared_ptr<service::MachineService> &machineService,
                                  QObject *parent = nullptr);

 void sendLiftToLoad();

 public slots:
  void onStartedStateMachine();
  void onFinishedStateMachine();

 private:
  QTimer liftMovingTimeOut;
  QStateMachine *qmachine = new QStateMachine;
  std::shared_ptr<service::BrokerService> brokerService;
  std::shared_ptr<IODeviceService> deviceService;
  std::shared_ptr<service::MachineService> machineService;

  void defineLiftTransitionStates();

 private slots:
  void postUpdateProximityBinDrop(bool status);
  void postUpdateProximityBinLoad(bool status);
  void postUpdateRelayLiftUp(bool status);
  void postUpdateRelayLiftDown(bool status);

  void toggleLiftDownRelay();
  void startLiftTimeOut();

};

#endif //BSF_STATEMACHINEAPPSERVICE_H_
