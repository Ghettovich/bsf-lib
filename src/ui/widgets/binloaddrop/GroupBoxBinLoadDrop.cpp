#include "ui_groupboxbinloaddrop.h"
#include "GroupBoxBinLoadDrop.h"
#include <BsfWidgetEnum.h>

GroupBoxBinLoadDrop::GroupBoxBinLoadDrop(QWidget *parent, const Qt::WindowFlags &f, MqttClient *_m_client)  :
    QWidget(parent, f)
    , ui(new Ui::GroupBoxBinLoadDrop)
    , m_client(_m_client) {
    ui->setupUi(this);
    QVariant formId = WIDGET_TYPES::GROUPBOX_BIN_LOAD_DROP;
    this->setProperty("formId", formId);

    relayBinLoad = new Relay(32, IODevice::LOW); // Digital
    relayBinDrop = new Relay(33, IODevice::LOW); // Digital
    proximityBinDrop = new DetectionSensor(10, IODevice::HIGH); // PULL UP (HIGH = OFF!)

    init();
}
GroupBoxBinLoadDrop::~GroupBoxBinLoadDrop() {
    delete ui;
}
void GroupBoxBinLoadDrop::init()
{
    ui->labelProximityBinDropStatus->setText("");
    setProximityBinDropLabelStatus();

    connect(ui->pushButtonBinLoadRelay, &QPushButton::clicked,
            this, &GroupBoxBinLoadDrop::onClickPushButtonBinLoad);
    connect(ui->pushButtonBinDropRelay, &QPushButton::clicked,
            this, &GroupBoxBinLoadDrop::onClickPushButtonBinDrop);

    connect(m_client, &MqttClient::receivedNewIODeviceStates,
            this, &GroupBoxBinLoadDrop::onUpdateIODevices);
}
void GroupBoxBinLoadDrop::setProximityBinDropLabelStatus()
{
    if(proximityBinDrop->getDeviceState() == IODevice::HIGH) {
        ui->labelProximityBinDropStatus->setStyleSheet("QLabel { background-color : red }");
    } else if(proximityBinDrop->getDeviceState() == IODevice::LOW) {
        ui->labelProximityBinDropStatus->setStyleSheet("QLabel { background-color : green }");
    }
}
void GroupBoxBinLoadDrop::setBinLoadButtonState()
{
    if(relayBinLoad->isDeviceStateLOW()) {
        ui->pushButtonBinLoadRelay->setStyleSheet("QLabel { background-color : green }");
    } else {
        ui->pushButtonBinLoadRelay->setStyleSheet("QLabel { background-color : red }");
    }
}
void GroupBoxBinLoadDrop::setBinDropButtonState()
{
    if(relayBinDrop->isDeviceStateLOW()) {
        ui->pushButtonBinDropRelay->setStyleSheet("QLabel { background-color : green }");
    } else {
        ui->pushButtonBinDropRelay->setStyleSheet("QLabel { background-color : red }");
    }
}
void GroupBoxBinLoadDrop::updateRelayStates(const Relay &_relay)
{
    if(_relay.getId() == relayBinLoad->getId()) {
        relayBinLoad->setDeviceState(_relay.getDeviceState());
        setBinLoadButtonState();
    } else if (_relay.getId() == relayBinDrop->getId()) {
        relayBinDrop->setDeviceState(_relay.getDeviceState());
        setBinDropButtonState();
    }
}
void GroupBoxBinLoadDrop::updateProximityState(const DetectionSensor &_detectionSensor)
{
    if(proximityBinDrop->getId() == _detectionSensor.getId()) {
        proximityBinDrop->setDeviceState(_detectionSensor.getDeviceState());
        setProximityBinDropLabelStatus();
    }
}
void GroupBoxBinLoadDrop::onClickPushButtonBinLoad()
{
    QJsonObject jsonPayload;
    jsonPayload["toggle"] = relayBinLoad->getId();

    m_client->publish("/toggle/relay", jsonPayload);
}
void GroupBoxBinLoadDrop::onClickPushButtonBinDrop()
{
    QJsonObject jsonPayload;
    jsonPayload["toggle"] = relayBinDrop->getId();

    m_client->publish("/toggle/relay", jsonPayload);
}
void GroupBoxBinLoadDrop::onUpdateIODevices(const QVector<IODevice *> &iodeviceList)
{
    for(const auto iodevice : iodeviceList) {
        if(typeid(iodevice) == typeid(Relay)) {
            Relay relay = dynamic_cast<Relay&>(*iodevice);
            updateRelayStates(relay);
        } else if (typeid(iodevice) == typeid(DetectionSensor)) {
            DetectionSensor proximity = dynamic_cast<DetectionSensor&>(*iodevice);
            updateProximityState(proximity);
        }
    }
}
