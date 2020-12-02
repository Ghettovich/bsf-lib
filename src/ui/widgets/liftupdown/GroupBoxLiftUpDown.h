#ifndef BSF_LIB_GROUPBOXLIFTUPDOWN_H
#define BSF_LIB_GROUPBOXLIFTUPDOWN_H

namespace Ui
{
class GroupBoxLiftUpDown;
}

#include <iodevice.h>
#include <QtWidgets/QWidget>
#include <MqttClient.h>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>

class GroupBoxLiftUpDown: public QWidget
{

Q_OBJECT

public:
    GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f);
    GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f, MqttClient *_m_client);
    virtual ~GroupBoxLiftUpDown();
    void init();
    void setProximityBinLoadSubscription(QMqttSubscription *sub);

public slots:
    void onUpdateMessage(const QMqttMessage &msg);
    void onUpdateStatus(QMqttSubscription::SubscriptionState state);

private:
    Ui::GroupBoxLiftUpDown *ui = nullptr;
    MqttClient *m_client = nullptr;
    QMqttSubscription *m_sub = nullptr;
    IODevice *relayBinLiftUp;
    IODevice *relayBinLiftDown;

private slots:
    void onClickPushButtonLiftDown();
    void onClickPushButtonLiftUp();

};


#endif //BSF_LIB_GROUPBOXLIFTUPDOWN_H