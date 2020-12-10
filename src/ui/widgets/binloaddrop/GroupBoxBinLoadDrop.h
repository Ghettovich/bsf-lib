#ifndef BSF_LIB_GROUPBOXBINLOADDROP_H
#define BSF_LIB_GROUPBOXBINLOADDROP_H

namespace Ui
{
class GroupBoxBinLoadDrop;
}

#include <iodevice.h>
#include <relay.h>
#include <detectionsensor.h>
#include <MqttClient.h>
#include <fonts/MaterialRegular.h>
#include <QObject>
#include <QtWidgets/QWidget>

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
    Ui::GroupBoxBinLoadDrop *ui = nullptr;
    MaterialRegular materialRegular;
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
