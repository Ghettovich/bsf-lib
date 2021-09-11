#ifndef BSF_STATEMACHINE_QT_EXAMPLE_LIFTTRANSITION_H_
#define BSF_STATEMACHINE_QT_EXAMPLE_LIFTTRANSITION_H_

#include <QEvent>
#include <QDebug>
#include <QAbstractTransition>

struct LiftEvent : public QEvent {
  LiftEvent(bool proximityLoad, bool proximityDrop, bool relayLiftOn) :
      QEvent(QEvent::Type(QEvent::User + 2)),
      relayLiftOn(relayLiftOn),
      proximityLoad(proximityLoad),
      proximityDrop(proximityDrop) {};

  bool relayLiftOn;
  bool proximityLoad;
  bool proximityDrop;
};

class LiftTransition : public QAbstractTransition
{
  Q_OBJECT

 public:
  LiftTransition(bool proximityLoad, bool proximityDrop, bool relayLiftOn):
  m_proximityLoad(proximityLoad),
  m_proximityDrop(proximityDrop),
  m_relayOn(relayLiftOn) {}

 protected:
  bool eventTest(QEvent *e) override
  {
    if (e->type() != QEvent::Type(QEvent::User+2)) {// StringEvent
      return false;
    }

    qDebug() << "Got lift transition event";
    auto *se = dynamic_cast<LiftEvent*>(e);
    return (m_proximityLoad == se->proximityLoad &&
        m_proximityDrop == se->proximityDrop &&
        m_relayOn == se->relayLiftOn);
  }

  void onTransition(QEvent *) override {}

 private:
  bool m_relayOn;
  bool m_proximityLoad;
  bool m_proximityDrop;
};

#endif //BSF_STATEMACHINE_QT_EXAMPLE_LIFTTRANSITION_H_
