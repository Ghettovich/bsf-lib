#ifndef SUBSCRIPTIONWINDOW_H
#define SUBSCRIPTIONWINDOW_H

namespace Ui {
class SubscriptionWindow;
}

#include <QtWidgets/QWidget>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>

class SubscriptionWindow : public QWidget
{

Q_OBJECT

public:
    SubscriptionWindow(QMqttSubscription *m_sub);
    virtual ~SubscriptionWindow();

public slots:
    void onUpdateMessage(const QMqttMessage &msg);
    void onUpdateStatus(QMqttSubscription::SubscriptionState state);

private:
    Ui::SubscriptionWindow *ui = nullptr;
    QMqttSubscription *m_sub;
};


#endif //SUBSCRIPTIONWINDOW_H
