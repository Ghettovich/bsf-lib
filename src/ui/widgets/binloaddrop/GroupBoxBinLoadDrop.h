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

public slots:
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList);

private:
    const QString toggleRelayTopic = "/toggle/relay";
    //MaterialRegular fonts;
    Ui::GroupBoxBinLoadDrop *ui = nullptr;
    MqttClient *m_client = nullptr;
    IODevice *relayBinLoad = nullptr;
    IODevice *relayBinDrop = nullptr;
    IODevice *proximityBinDrop = nullptr;

    void setProximityBinDropLabelStatus();
    void setBinLoadButtonState();
    void setBinDropButtonState();

private slots:
    void onClickPushButtonBinLoad();
    void onClickPushButtonBinDrop();
};


#endif //BSF_LIB_GROUPBOXBINLOADDROP_H
