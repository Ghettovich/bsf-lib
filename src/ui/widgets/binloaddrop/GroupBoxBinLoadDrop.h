#ifndef BSF_LIB_GROUPBOXBINLOADDROP_H
#define BSF_LIB_GROUPBOXBINLOADDROP_H

namespace Ui
{
class GroupBoxBinLoadDrop;
}

#include <QObject>
#include <iodevice.h>
#include <relay.h>
#include <detectionsensor.h>
#include <QtWidgets/QWidget>
#include <MqttClient.h>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>

class GroupBoxBinLoadDrop: public QWidget
{

Q_OBJECT

public:
    explicit GroupBoxBinLoadDrop(QWidget *parent, const Qt::WindowFlags &f, MqttClient *_m_client);
    virtual ~GroupBoxBinLoadDrop();
    void init();
    //void createSubscriptions();

public slots:
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList);

//    void onUpdateMessage(const QMqttMessage &msg);
//    void onUpdateStatus(QMqttSubscription::SubscriptionState state);
//
//    void onUpdateMessageRelayStates(const QMqttMessage &msg);
//    void onUpdateStatusRelayStates(QMqttSubscription::SubscriptionState state);

private:
    Ui::GroupBoxBinLoadDrop *ui = nullptr;
    MqttClient *m_client = nullptr;
//    QMqttSubscription *proximitySub = nullptr;
//    QMqttSubscription *relayStateSub = nullptr;
    IODevice *relayBinLoad = nullptr;
    IODevice *relayBinDrop = nullptr;
    IODevice *proximityBinDrop = nullptr;

    void setProximityBinDropLabelStatus();
    void setBinLoadButtonState();
    void setBinDropButtonState();
    void updateRelayStates(const Relay &_relay);
    void updateProximityState(const DetectionSensor &_detectionSensor);

private slots:
    void onClickPushButtonBinLoad();
    void onClickPushButtonBinDrop();
};


#endif //BSF_LIB_GROUPBOXBINLOADDROP_H
