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

//  QObject::connect(machineService.get(), &service::MachineService::relayBinDropChanged,
//                   this, &StateMachineAppService::postUpdateRelayBinDropChanged);

  QObject::connect(machineService.get(), &service::MachineService::hydraulicChanged,
                   this, &StateMachineAppService::postUpdateRelayHydraulic);
}

void StateMachineAppService::sendBinToLoad() {
  // Check if bin is tilted, if true need to send bin to load
  if (deviceService->isBinAtDrop()) {
    auto *s1 = new QState(); // Inital state
    auto *s2 = new QFinalState();

    defineTransitionsBinDropToLoad(s1, s2);

    qmachine->addState(s1);
    qmachine->addState(s2);
    qmachine->setInitialState(s1);

    connections << QObject::connect(machineService.get(), &service::MachineService::proximityLoadChanged,
                     this, &StateMachineAppService::postUpdateProximityBinLoad);

    connections << QObject::connect(machineService.get(), &service::MachineService::proximityDropChanged,
                     this, &StateMachineAppService::postUpdateProximityBinDrop);

    connections << QObject::connect(machineService.get(), &service::MachineService::relayBinLoadChanged,
                     this, &StateMachineAppService::postUpdateRelayBinLoadChanged);

    connections << QObject::connect(qmachine, &QStateMachine::started, this, &StateMachineAppService::onStartLiftDropToLoad);
    connections << QObject::connect(qmachine, &QStateMachine::finished, this, &StateMachineAppService::onFinishedStateMachine);

    if (!qmachine->isRunning()) {
      machineState = DROP_TO_LOAD;
      qmachine->start();
    }
  } else {
    qDebug() << "bin not tiled, do nothing";
  }
}

void StateMachineAppService::sendLiftToBottom() {

  if(deviceService->isBinAtTop()) {
    auto *s1 = new QState(); // Inital state
    auto *s2 = new QFinalState();

    defineTransitionsLiftTopToBottom(s1, s2);

    qmachine->addState(s1);
    qmachine->addState(s2);
    qmachine->setInitialState(s1);

    connections << QObject::connect(machineService.get(), &service::MachineService::proximityLiftTopChanged,
                     this, &StateMachineAppService::postUpdateProximityLiftTop);

    connections << QObject::connect(machineService.get(), &service::MachineService::proximityLiftBottomChanged,
                     this, &StateMachineAppService::postUpdateProximityLiftBottom);

    connections << QObject::connect(machineService.get(), &service::MachineService::relayLiftDownChanged,
                     this, &StateMachineAppService::postUpdateRelayLiftDown);

    connections << QObject::connect(qmachine, &QStateMachine::started, this, &StateMachineAppService::onStartLiftTopToBottom);
    connections << QObject::connect(qmachine, &QStateMachine::finished, this, &StateMachineAppService::onFinishedStateMachine);

    if (!qmachine->isRunning()) {
      machineState = LIFT_TOP_TO_BOTTOM;
      qmachine->start();
    }

  } else {
    qDebug() << "Bin is already at bottom, do nothing";
  }
}

void StateMachineAppService::sendLiftToLoad() {

}

void StateMachineAppService::sendBinToDrop() {

}


void StateMachineAppService::defineTransitionsLiftTopToBottom(QState *initialState, QFinalState *finalState) {
  auto *s11 = new QState(initialState); // Lift idle. Bin at drop and lift at bottom.
  auto *s12 = new QState(initialState); // Lift moving. Bin undetected, relay ON.
  auto *s13 = new QState(initialState); // Lift arrived. Bin detected at load. Relay still ON.
  auto *s14 = new QState(initialState); // Lift arrived. Bin detected at load. Relay is now OFF.

  initialState->setInitialState(s11);

  auto *t1 = new LiftTransition(false, true, false, false);
  t1->setTargetState(s12);
  s11->addTransition(t1);

  auto *t2 = new LiftTransition(false, false, true, true);
  t2->setTargetState(s13);
  s12->addTransition(t2);

  auto *t3 = new LiftTransition(true, false, true, true);
  t3->setTargetState(s14);
  s13->addTransition(t3);

  auto *t4 = new LiftTransition(true, false, false, false);
  t4->setTargetState(finalState);
  s14->addTransition(t4);

  QObject::connect(s12, &QState::entered, this, &StateMachineAppService::toggleLiftDownRelay);
  QObject::connect(s13, &QState::entered, this, &StateMachineAppService::startLiftTimeOut);
  QObject::connect(s14, &QState::entered, this, &StateMachineAppService::toggleLiftDownRelay);
}

void StateMachineAppService::defineTransitionsBinDropToLoad(QState *initialState, QFinalState *finalState) {
  auto *s11 = new QState(initialState); // Bin at drop and lift positioned at top.
  auto *s12 = new QState(initialState); // Lift moving from top to bottom. Bin undetected, hydraulic on.
  auto *s13 = new QState(initialState); // Bin arrived at bottom. Relays still on.
  auto *s14 = new QState(initialState); // Bin arrived at bottom and relays off.

  initialState->setInitialState(s11);

  auto *t1 = new LiftTransition(false, true, false, false);
  t1->setTargetState(s12);
  s11->addTransition(t1);

  auto *t2 = new LiftTransition(false, false, true, true);
  t2->setTargetState(s13);
  s12->addTransition(t2);

  auto *t3 = new LiftTransition(true, false, true, true);
  t3->setTargetState(s14);
  s13->addTransition(t3);

  auto *t4 = new LiftTransition(true, false, false, false);
  t4->setTargetState(finalState);
  s14->addTransition(t4);

  QObject::connect(s12, &QState::entered, this, &StateMachineAppService::toggleBinLoadRelay);
  QObject::connect(s13, &QState::entered, this, &StateMachineAppService::startLiftTimeOut);
  QObject::connect(s14, &QState::entered, this, &StateMachineAppService::toggleBinLoadRelay);
}

void StateMachineAppService::toggleLiftDownRelay() {
  qDebug() << "toggling lift relay";

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  int relayLiftDownId = settings->value("liftdown").toInt();
  int hydraulicId = settings->value("hydraulic").toInt();

  brokerService->toggleRelay(hydraulicId);
  brokerService->toggleRelay(relayLiftDownId);
}

void StateMachineAppService::toggleBinLoadRelay() {
  qDebug() << "toggling bin load relay";

  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");

  int binLoadRelayId = settings->value("binload").toInt();
  int hydraulicRelayId = settings->value("hydraulic").toInt();

  brokerService->toggleRelay(hydraulicRelayId);
  brokerService->toggleRelay(binLoadRelayId);
}

void StateMachineAppService::startLiftTimeOut() {
  liftMovingTimeOut.start(5000);
}

void StateMachineAppService::onStartLiftDropToLoad() {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");
  bool loadRelay = deviceService->isDeviceOn(settings->value("binload").toInt());
  bool hydraulicRelay = deviceService->isDeviceOn(settings->value("hydraulic").toInt());
  settings->endGroup();

  settings->beginGroup("detectionsensor");
  bool drop = deviceService->isDeviceOn(settings->value("bindrop").toInt());
  bool load = deviceService->isDeviceOn(settings->value("binload").toInt());
  settings->endGroup();

  qmachine->postEvent(new LiftTransitionEvent(load, drop, loadRelay, hydraulicRelay));
}

void StateMachineAppService::onStartLiftTopToBottom() {
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("relays");
  bool liftdown = deviceService->isDeviceOn(settings->value("liftdown").toInt());
  bool hydraulic = deviceService->isDeviceOn(settings->value("hydraulic").toInt());
  settings->endGroup();

  settings->beginGroup("detectionsensor");
  bool lifttop = deviceService->isDeviceOn(settings->value("lifttop").toInt());
  bool liftbottom = deviceService->isDeviceOn(settings->value("liftbottom").toInt());
  settings->endGroup();

  qmachine->postEvent(new LiftTransitionEvent(liftbottom, lifttop, liftdown, hydraulic));
}

void StateMachineAppService::onFinishedStateMachine() {
  qDebug() << "Statemachine finished.";
  machineState = IDLE;
  connections.clear();
  qmachine->stop();
}

void StateMachineAppService::postUpdateProximityBinDrop(bool status) {
  if (qmachine->isRunning()) {
    qDebug() << "posting new proximity bin drop";

    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("relays");
    bool relayStatus = deviceService->isDeviceOn(settings->value("binload").toInt());
    bool hydraulic = deviceService->isDeviceOn(settings->value("hydraulic").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool binLoadStatus = deviceService->isDeviceOn(settings->value("binload").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftTransitionEvent(binLoadStatus, status, relayStatus, hydraulic));
  }
}
void StateMachineAppService::postUpdateProximityBinLoad(bool status) {
  if (qmachine->isRunning()) {
    qDebug() << "posting new proximity bin load";

    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("relays");
    bool relayStatus = deviceService->isDeviceOn(settings->value("binload").toInt());
    bool hydraulic = deviceService->isDeviceOn(settings->value("hydraulic").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool binDropStatus = deviceService->isDeviceOn(settings->value("bindrop").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftTransitionEvent(status, binDropStatus, relayStatus, hydraulic));
  }
}
void StateMachineAppService::postUpdateRelayLiftUp(bool status) {

}
void StateMachineAppService::postUpdateRelayLiftDown(bool status) {
  if (qmachine->isRunning()) {
    qDebug() << "posting new relay state lift down";

    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("relays");
    bool hydraulic = deviceService->isDeviceOn(settings->value("hydraulic").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool lifttop = deviceService->isDeviceOn(settings->value("lifttop").toInt());
    bool liftbottom = deviceService->isDeviceOn(settings->value("liftbottom").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftTransitionEvent(liftbottom, lifttop, status, hydraulic));
  }
}

void StateMachineAppService::postUpdateProximityLiftTop(bool status) {
  if (qmachine->isRunning()) {
    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("relays");
    bool liftdown = deviceService->isDeviceOn(settings->value("liftdown").toInt());
    bool hydraulic = deviceService->isDeviceOn(settings->value("hydraulic").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool liftbottom = deviceService->isDeviceOn(settings->value("liftbottom").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftTransitionEvent(liftbottom, status, liftdown, hydraulic));
  }
}
void StateMachineAppService::postUpdateProximityLiftBottom(bool status) {
  if (qmachine->isRunning()) {
    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("relays");
    bool liftdown = deviceService->isDeviceOn(settings->value("liftdown").toInt());
    bool hydraulic = deviceService->isDeviceOn(settings->value("hydraulic").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool lifttop = deviceService->isDeviceOn(settings->value("lifttop").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftTransitionEvent(status, lifttop, liftdown, hydraulic));
  }
}
void StateMachineAppService::postUpdateRelayBinLoadChanged(bool status) {
  if (qmachine->isRunning()) {
    qDebug() << "posting new relay state bin load";

    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("relays");
    bool hydraulic = deviceService->isDeviceOn(settings->value("hydraulic").toInt());
    settings->endGroup();

    settings->beginGroup("detectionsensor");
    bool drop = deviceService->isDeviceOn(settings->value("bindrop").toInt());
    bool load = deviceService->isDeviceOn(settings->value("binload").toInt());
    settings->endGroup();

    qmachine->postEvent(new LiftTransitionEvent(load, drop, status, hydraulic));
  }
}
void StateMachineAppService::postUpdateRelayBinDropChanged(bool status) {

}
void StateMachineAppService::postUpdateRelayHydraulic(bool status) {
  if (qmachine->isRunning()) {
    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);

    if(machineState == DROP_TO_LOAD) {
      settings->beginGroup("relays");
      bool binloadRelay = deviceService->isDeviceOn(settings->value("binload").toInt());
      settings->endGroup();

      settings->beginGroup("detectionsensor");
      bool drop = deviceService->isDeviceOn(settings->value("bindrop").toInt());
      bool load = deviceService->isDeviceOn(settings->value("binload").toInt());

      qmachine->postEvent(new LiftTransitionEvent(load, drop, binloadRelay, status));
    } else if(machineState == LIFT_TOP_TO_BOTTOM) {
      settings->beginGroup("relays");
      bool liftdownRelay = deviceService->isDeviceOn(settings->value("liftdown").toInt());
      settings->endGroup();

      bool lifttop = deviceService->isDeviceOn(settings->value("lifttop").toInt());
      bool liftbottom = deviceService->isDeviceOn(settings->value("liftbottom").toInt());

      qmachine->postEvent(new LiftTransitionEvent(liftbottom, lifttop, liftdownRelay, status));
    }
  }
}
