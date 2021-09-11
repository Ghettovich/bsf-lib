#include "statemachine.appservice.h"
#include "LiftTransition.h"

#include <QDebug>
#include <QSettings>
#include <QState>

using namespace appservice;

StateMachineAppService::StateMachineAppService(std::shared_ptr<service::BrokerService> &_brokerService,
                                               std::shared_ptr<IODeviceService> &_deviceService,
                                               QObject *parent)
    : brokerService(_brokerService), deviceService(_deviceService), QObject(parent) {

  QObject::connect(&liftMovingTimeOut, &QTimer::timeout, [=]() {
    qDebug() << "Lift time out occured";
  });

}

void StateMachineAppService::onIODeviceChange(int deviceId, bool status) {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);

  if(deviceId < 10) {
    settings->beginGroup("weightsensor");
  } else if (deviceId < 20) {
    settings->beginGroup("detectionsensor");
  } else if (deviceId < 50) {
    settings->beginGroup("relays");
  }

  qDebug() << "statemachine onIODeviceChange device id = " << deviceId;

  if (settings->value("liftdown").toInt() == deviceId) {
    qDebug() << "posting new relay state lift down";

    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool binLoadStatus = deviceService->isDeviceOn(settings->value("binload").toInt());
    bool binDropStatus = deviceService->isDeviceOn(settings->value("bindrop").toInt());

    qmachine->postEvent(new LiftEvent(binLoadStatus, binDropStatus, status));
  } else if (settings->value("bindrop").toInt() == deviceId) {
    qDebug() << "posting new proximity bin drop";

    settings->endGroup();

    settings->beginGroup("relays");
    bool relayStatus = deviceService->isDeviceOn(settings->value("liftdown").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool binLoadStatus = deviceService->isDeviceOn(settings->value("binload").toInt());

    qmachine->postEvent(new LiftEvent(binLoadStatus, status, relayStatus));
  } else if (settings->value("binload").toInt() == deviceId) {
    qDebug() << "posting new proximity bin load";

    settings->endGroup();

    settings->beginGroup("relays");
    bool relayStatus = deviceService->isDeviceOn(settings->value("liftdown").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool binDropStatus = deviceService->isDeviceOn(settings->value("bindrop").toInt());

    qmachine->postEvent(new LiftEvent(status, binDropStatus, relayStatus));
  }
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

  QFinalState *s2 = new QFinalState();

  s1->setInitialState(s11);
  qmachine->addState(s1);

  LiftTransition *t1 = new LiftTransition(false, true, false);
  t1->setTargetState(s12);
  s11->addTransition(t1);

  LiftTransition *t2 = new LiftTransition(false, false, true);
  t2->setTargetState(s13);
  s12->addTransition(t2);

  LiftTransition *t3 = new LiftTransition(true, false, true);
  t3->setTargetState(s14);
  s13->addTransition(t3);

  LiftTransition *t4 = new LiftTransition(true, false, false);
  t4->setTargetState(s2);
  s14->addTransition(t4);

  qmachine->addState(s2);
  qmachine->setInitialState(s1);

  QObject::connect(s11, &QState::entered, [=](){
    qDebug() << "Entered s11. Ok to send lift to load";
  });

  QObject::connect(s12, &QState::entered, this, &StateMachineAppService::toggleLiftDownRelay);
  QObject::connect(s13, &QState::entered, this, &StateMachineAppService::startLiftTimeOut);
  QObject::connect(s14, &QState::entered, this, &StateMachineAppService::toggleLiftDownRelay);

  QObject::connect(s11, &QState::exited, [=](){
    qDebug() << "Exited S11";
  });

  QObject::connect(s12, &QState::exited, [=](){
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

  qmachine->postEvent(new LiftEvent(binLoadStatus, binDropStatus, relayStatus));

  qDebug() << "posted current state";

  QObject::connect(deviceService.get(), &IODeviceService::stateChangdIODevice,
                   this, &StateMachineAppService::StateMachineAppService::onIODeviceChange);
}

void StateMachineAppService::onFinishedStateMachine() {
  qDebug() << "Finished sending lift to load.";
}