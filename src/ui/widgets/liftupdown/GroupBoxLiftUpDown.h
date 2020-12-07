#ifndef BSF_LIB_GROUPBOXLIFTUPDOWN_H
#define BSF_LIB_GROUPBOXLIFTUPDOWN_H

namespace Ui
{
class GroupBoxLiftUpDown;
}

#include <iodevice.h>
#include <relay.h>
#include <detectionsensor.h>
#include <QtWidgets/QWidget>
#include <MqttClient.h>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>

class GroupBoxLiftUpDown: public QWidget
{

Q_OBJECT

public:
    GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f, MqttClient *_m_client);
    virtual ~GroupBoxLiftUpDown();
    void init();

public slots:
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList);

//    void onUpdateMessage(const QMqttMessage &msg);
//    void onUpdateStatus(QMqttSubscription::SubscriptionState state);
//
//    void onUpdateMessageRelayStates(const QMqttMessage &msg);
//    void onUpdateStatusRelayStates(QMqttSubscription::SubscriptionState state);

private:
    Ui::GroupBoxLiftUpDown *ui = nullptr;
    MqttClient *m_client = nullptr;
    QMqttSubscription *proximitySub = nullptr;
    QMqttSubscription *relayStateSub = nullptr;
    IODevice *relayBinLiftUp;
    IODevice *relayBinLiftDown;
    IODevice *proximityBinLoad;

    void setProximityBinLoadStatusLabel();
    void setLiftUpButtonState();
    void setLiftDownButtonState();
    void updateRelayStates(const Relay &_relay);
    void updateProximityState(const DetectionSensor &_detectionSensor);

private slots:
    void onClickPushButtonLiftDown();
    void onClickPushButtonLiftUp();

};


#endif //BSF_LIB_GROUPBOXLIFTUPDOWN_H
