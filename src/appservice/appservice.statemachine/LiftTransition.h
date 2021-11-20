#ifndef BSF_LIB_APPSERVICE_STATEMACHINE_LIFTTOPBOTTOMTRANSITION_H_
#define BSF_LIB_APPSERVICE_STATEMACHINE_LIFTTOPBOTTOMTRANSITION_H_

#include <QEvent>
#include <QDebug>
#include <QAbstractTransition>

struct LiftTransitionEvent : public QEvent {

  LiftTransitionEvent(bool proximity1, bool proximity2, bool relay1, bool relay2) :
      QEvent(QEvent::Type(QEvent::User + 3)),
      proximity1(proximity1),
      proximity2(proximity2),
      relay1(relay1),
      relay2(relay2) {};

  bool relay1, relay2;
  bool proximity1, proximity2;
};

class LiftTransition : public QAbstractTransition
{
 Q_OBJECT

 public:
  LiftTransition(bool proximity1, bool proximity2, bool relay1, bool relay2):
      m_proximity1(proximity1),
      m_proximity2(proximity2),
      m_relay1(relay1),
      m_relay2(relay2) {}

 protected:
  bool eventTest(QEvent *e) override
  {
    if (e->type() != QEvent::Type(QEvent::User+3)) {// LiftEvent
      return false;
    }

    qDebug() << "Got lift transition event";
    auto *se = dynamic_cast<LiftTransitionEvent*>(e);
    return (m_proximity1 == se->proximity1 &&
        m_proximity2 == se->proximity2 &&
        m_relay1 == se->relay1 &&
        m_relay2 == se->relay2);
  }

  void onTransition(QEvent *) override {}

 private:
  bool m_relay1, m_relay2;
  bool m_proximity1, m_proximity2;
};

#endif //BSF_LIB_APPSERVICE_STATEMACHINE_LIFTTOPBOTTOMTRANSITION_H_
