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

  enum MACHINE_STATE {
    IDLE, LOAD_TO_DROP, DROP_TO_LOAD, LIFT_BOTTOM_TO_TOP, LIFT_TOP_TO_BOTTOM
  };
  Q_ENUM(MACHINE_STATE);

  explicit StateMachineAppService(std::shared_ptr<service::BrokerService> &brokerService,
                                  std::shared_ptr<IODeviceService> &deviceService,
                                  std::shared_ptr<service::MachineService> &machineService,
                                  QObject *parent = nullptr);

  void sendBinToLoad();
  void sendBinToDrop();
  void sendLiftToBottom();
  void sendLiftToLoad();

 public slots:
  void onStartLiftDropToLoad();
  void onStartLiftTopToBottom();
  void onFinishedStateMachine();

 private:
  MACHINE_STATE machineState = IDLE;
  QTimer liftMovingTimeOut;
  QStateMachine *qmachine = new QStateMachine;
  QList<QMetaObject::Connection> connections;
  std::shared_ptr<service::BrokerService> brokerService;
  std::shared_ptr<IODeviceService> deviceService;
  std::shared_ptr<service::MachineService> machineService;

  void defineTransitionsBinDropToLoad(QState *initialState, QFinalState *finalState);
  void defineTransitionsLiftTopToBottom(QState *initialState, QFinalState *finalState);

 private slots:
  void postUpdateProximityBinDrop(bool status);
  void postUpdateProximityBinLoad(bool status);
  void postUpdateProximityLiftTop(bool status);
  void postUpdateProximityLiftBottom(bool status);
  void postUpdateRelayLiftUp(bool status);
  void postUpdateRelayLiftDown(bool status);
  void postUpdateRelayBinLoadChanged(bool status);
  void postUpdateRelayBinDropChanged(bool status);
  void postUpdateRelayHydraulic(bool status);

  void toggleBinLoadRelay();
  void toggleLiftDownRelay();
  void startLiftTimeOut();



};

#endif //BSF_STATEMACHINEAPPSERVICE_H_
