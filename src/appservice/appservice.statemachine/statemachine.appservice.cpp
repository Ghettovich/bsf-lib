#include "statemachine.appservice.h"
#include "LiftTransition.h"

#include <QDebug>
#include <QSettings>
#include <QState>

using namespace appservice;

StateMachineAppService::StateMachineAppService(std::shared_ptr<service::BrokerService> &_brokerService,
                                               std::shared_ptr<IODeviceService> &_deviceService,
                                               std::shared_ptr<service::MachineService> &_machineService,
                                               QObject *parent)
    : brokerService(_brokerService), deviceService(_deviceService), machineService(_machineService), QObject(parent) {

  QObject::connect(&liftMovingTimeOut, &QTimer::timeout, [=]() {
    qDebug() << "Lift time out occured";
  });

  QObject::connect(deviceService.get(), &IODeviceService::stateChangdIODevice,
                   machineService.get(), &service::MachineService::onIODeviceChange);

  QObject::connect(machineService.get(), &service::MachineService::proximityLoadChanged,
                   this, &StateMachineAppService::postUpdateProximityBinLoad);

  QObject::connect(machineService.get(), &service::MachineService::proximityDropChanged,
                   this, &StateMachineAppService::postUpdateProximityBinDrop);

  QObject::connect(machineService.get(), &service::MachineService::relayLiftDownChanged,
                   this, &StateMachineAppService::postUpdateRelayLiftDown);
}

void StateMachineAppService::sendLiftToLoad() {
  defineLiftTransitionStates();

  if (!qmachine->isRunning()) {
    qmachine->start();
  }
}

void StateMachineAppService::defineLiftTransitionStates() {
  auto *s1 = new QState(); // Inital state
  auto *s11 = new QState(s1); // Lift idle. Bin at drop.
  auto *s12 = new QState(s1); // Lift moving. Bin undetected, relay ON.
  auto *s13 = new QState(s1); // Lift arrived. Bin detected at load. Relay still ON.
  auto *s14 = new QState(s1); // Lift arrived. Bin detected at load. Relay is now OFF.

  auto *s2 = new QFinalState();

  s1->setInitialState(s11);
  qmachine->addState(s1);

  auto *t1 = new LiftTransition(false, true, false);
  t1->setTargetState(s12);
  s11->addTransition(t1);

  auto *t2 = new LiftTransition(false, false, true);
  t2->setTargetState(s13);
  s12->addTransition(t2);

  auto *t3 = new LiftTransition(true, false, true);
  t3->setTargetState(s14);
  s13->addTransition(t3);

  auto *t4 = new LiftTransition(true, false, false);
  t4->setTargetState(s2);
  s14->addTransition(t4);

  qmachine->addState(s2);
  qmachine->setInitialState(s1);

  QObject::connect(s11, &QState::entered, [=]() {
    qDebug() << "Entered s11. Ok to send lift to load";
  });

  QObject::connect(s12, &QState::entered, this, &StateMachineAppService::toggleLiftDownRelay);
  QObject::connect(s13, &QState::entered, this, &StateMachineAppService::startLiftTimeOut);
  QObject::connect(s14, &QState::entered, this, &StateMachineAppService::toggleLiftDownRelay);

  QObject::connect(s11, &QState::exited, [=]() {
    qDebug() << "Exited S11";
  });

  QObject::connect(s12, &QState::exited, [=]() {
    qDebug() << "Exited S12";
  });

  QObject::connect(qmachine, &QStateMachine::started, this, &StateMachineAppService::onStartedStateMachine);
  QObject::connect(qmachine, &QStateMachine::finished, this, &StateMachineAppService::onFinishedStateMachine);
}
void StateMachineAppService::toggleLiftDownRelay() {
  qDebug() << "toggling lift relay";

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  int relayLiftDownId = settings->value("liftdown").toInt();
  brokerService->toggleRelay(relayLiftDownId);
}
void StateMachineAppService::startLiftTimeOut() {
  liftMovingTimeOut.start(30000);
}
void StateMachineAppService::onStartedStateMachine() {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");
  bool relayStatus = deviceService->isDeviceOn(settings->value("liftdown").toInt());
  settings->endGroup();

  settings->beginGroup("detectionsensor");
  bool binLoadStatus = deviceService->isDeviceOn(settings->value("binload").toInt());
  bool binDropStatus = deviceService->isDeviceOn(settings->value("bindrop").toInt());
  settings->endGroup();

  qmachine->postEvent(new LiftEvent(binLoadStatus, binDropStatus, relayStatus));

  qDebug() << "posted current state";
}

void StateMachineAppService::onFinishedStateMachine() {
  qDebug() << "Finished sending lift to load.";
}
void StateMachineAppService::postUpdateProximityBinDrop(bool status) {
  if (qmachine->isRunning()) {
    qDebug() << "posting new proximity bin drop";

    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("relays");
    bool relayStatus = deviceService->isDeviceOn(settings->value("liftdown").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool binLoadStatus = deviceService->isDeviceOn(settings->value("binload").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftEvent(binLoadStatus, status, relayStatus));
  }
}
void StateMachineAppService::postUpdateProximityBinLoad(bool status) {
  if (qmachine->isRunning()) {

    qDebug() << "posting new proximity bin load";

    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("relays");
    bool relayStatus = deviceService->isDeviceOn(settings->value("liftdown").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool binDropStatus = deviceService->isDeviceOn(settings->value("bindrop").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftEvent(status, binDropStatus, relayStatus));
  }
}
void StateMachineAppService::postUpdateRelayLiftUp(bool status) {

}
void StateMachineAppService::postUpdateRelayLiftDown(bool status) {
  if(qmachine->isRunning()) {
    qDebug() << "posting new relay state lift down";

    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("detectionsensor");
    bool binLoadStatus = deviceService->isDeviceOn(settings->value("binload").toInt());
    bool binDropStatus = deviceService->isDeviceOn(settings->value("bindrop").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftEvent(binLoadStatus, binDropStatus, status));
  }
}
