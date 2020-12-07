#include "ui_groupboxliftupdown.h"
#include "GroupBoxLiftUpDown.h"
#include <BsfWidgetEnum.h>

GroupBoxLiftUpDown::GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f, MqttClient *_m_client)
    :
    QWidget(parent, f), ui(new Ui::GroupBoxLiftUpDown), m_client(_m_client)
{
    ui->setupUi(this);
    QVariant formId = WIDGET_TYPES::GROUPBOX_LIFT_UP_DOWN;
    this->setProperty("formId", formId);

    relayBinLiftDown = new Relay(31, IODevice::LOW); // Digital
    relayBinLiftUp = new Relay(30, IODevice::LOW); // Digital
    proximityBinLoad = new DetectionSensor(11, IODevice::HIGH); // PULL UP (HIGH = OFF!)

    init();
}

GroupBoxLiftUpDown::~GroupBoxLiftUpDown()
{
    if(!proximitySub) {
        proximitySub->unsubscribe();
    }
    delete ui;
}

void GroupBoxLiftUpDown::init()
{
    ui->labelProximityBinLoadStatus->setText("");
    setProximityBinLoadStatusLabel();
    setLiftDownButtonState();
    setLiftUpButtonState();

    connect(ui->pushButtonLiftDown, &QPushButton::clicked,
            this, &GroupBoxLiftUpDown::onClickPushButtonLiftDown);

    connect(ui->pushButtonLiftUp, &QPushButton::clicked,
            this, &GroupBoxLiftUpDown::onClickPushButtonLiftUp);
}
void GroupBoxLiftUpDown::onClickPushButtonLiftDown()
{
    QJsonObject jsonPayload;
    jsonPayload["toggle"] = relayBinLiftDown->getId();

    m_client->publish("/toggle/relay", jsonPayload);
    printf("\ndown clicked");
}
void GroupBoxLiftUpDown::onClickPushButtonLiftUp()
{
    QJsonObject jsonPayload;
    jsonPayload["toggle"] = relayBinLiftUp->getId();

    m_client->publish("/toggle/relay", jsonPayload);
    printf("\nUp clicked");
}
void GroupBoxLiftUpDown::setProximityBinLoadStatusLabel()
{
    if(proximityBinLoad->getDeviceState() == IODevice::HIGH) {
        ui->labelProximityBinLoadStatus->setStyleSheet("QLabel { background-color : red }");
    } else if(proximityBinLoad->getDeviceState() == IODevice::LOW) {
        ui->labelProximityBinLoadStatus->setStyleSheet("QLabel { background-color : green }");
    }
}
void GroupBoxLiftUpDown::setLiftUpButtonState()
{
    if(relayBinLiftUp->isDeviceStateLOW()) {
        ui->pushButtonLiftUp->setStyleSheet("QLabel { background-color : green }");
    } else {
        ui->pushButtonLiftUp->setStyleSheet("QLabel { background-color : red }");
    }
}
void GroupBoxLiftUpDown::setLiftDownButtonState()
{
    if(relayBinLiftDown->isDeviceStateLOW()) {
        ui->pushButtonLiftUp->setStyleSheet("QLabel { background-color : green }");
    } else {
        ui->pushButtonLiftUp->setStyleSheet("QLabel { background-color : red }");
    }
}
void GroupBoxLiftUpDown::updateRelayStates(const Relay &_relay)
{
    if(_relay.getId() == relayBinLiftUp->getId()) {
        relayBinLiftUp->setDeviceState(_relay.getDeviceState());
        setLiftUpButtonState();
    } else if (_relay.getId() == relayBinLiftDown->getId()) {
        relayBinLiftDown->setDeviceState(_relay.getDeviceState());
        setLiftDownButtonState();
    }
}
void GroupBoxLiftUpDown::updateProximityState(const DetectionSensor &_detectionSensor)
{
    if(proximityBinLoad->getId() == _detectionSensor.getId()) {
        proximityBinLoad->setDeviceState(_detectionSensor.getDeviceState());
        setProximityBinLoadStatusLabel();
    }
}
void GroupBoxLiftUpDown::onUpdateIODevices(const QVector<IODevice *> &iodeviceList)
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

