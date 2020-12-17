#ifndef BSF_LIB_GROUPBOXBELTFEEDERS_H
#define BSF_LIB_GROUPBOXBELTFEEDERS_H

namespace Ui {
    class GroupBoxBeltFeeders;
}

#include <iodevice.h>
#include <widgets/devicestatus/IOWidgetStatusInterface.h>
#include <detectionsensor.h>
#include <MqttClient.h>
#include <fonts/MaterialRegular.h>
#include <QObject>
#include <QtWidgets/QWidget>


class GroupBoxBeltFeeders : public IOWidgetStatusInterface
{
    Q_OBJECT
    Q_INTERFACES(IOWidgetStatusInterface)

public:
    explicit GroupBoxBeltFeeders(MqttClient *_m_client);

public slots:
    void onUpdateIODevice(const IODevice *ioDevice) override;
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) override;

private:
    const QString toggleRelayTopic = "/toggle/relay";
    Ui::GroupBoxBeltFeeders *ui = nullptr;
    MaterialRegular materialRegular;
    MqttClient *m_client = nullptr;
    IODevice *relayBeltForward = nullptr;
    IODevice *relayBeltReverse = nullptr;
    IODevice *relayFeeder1Foward = nullptr;
    IODevice *relayFeeder1Reverse = nullptr;
    IODevice *relayFeeder2Foward = nullptr;
    IODevice *relayFeeder2Reverse = nullptr;

    void init();
    void setBeltForwardButtonState();
    void setBeltReverseButtonState();
    void setFeeder1ForwardButtonState();
    void setFeeder1ReverseButtonState();
    void setFeeder2ForwardButtonState();
    void setFeeder2ReverseButtonState();

private slots:
    void onClickPushButtonBeltForward();
    void onClickPushButtonBeltReverse();
    void onClickPushButtonFeeder1Forward();
    void onClickPushButtonFeeder1Reverse();
    void onClickPushButtonFeeder2Forward();
    void onClickPushButtonFeeder2Reverse();
};


#endif //BSF_LIB_GROUPBOXBELTFEEDERS_H
