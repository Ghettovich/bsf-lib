#ifndef BSF_LIB_GROUPBOXLIFTUPDOWN_H
#define BSF_LIB_GROUPBOXLIFTUPDOWN_H

namespace Ui
{
class GroupBoxLiftUpDown;
}

#include <QObject>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>
#include <QtWidgets/QWidget>

class GroupBoxLiftUpDown: public QWidget
{

Q_OBJECT

public:
    GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f);
    GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f, QMqttSubscription *sub);
    void init();
    virtual ~GroupBoxLiftUpDown();

public slots:
    void onUpdateMessage(const QMqttMessage &msg);
    void onUpdateStatus(QMqttSubscription::SubscriptionState state);

private:
    Ui::GroupBoxLiftUpDown *ui = nullptr;
    QMqttSubscription *m_sub;

private slots:
    void onClickPushButtonLiftDown();
    void onClickPushButtonLiftUp();

};


#endif //BSF_LIB_GROUPBOXLIFTUPDOWN_H
