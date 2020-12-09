#include "ui_groupboxliftupdown.h"
#include "GroupBoxLiftUpDown.h"
#include <typeinfo>
#include <string>
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
    if (proximityBinLoad->isDeviceStateLOW()) {
        ui->labelProximityBinLoadStatus->setStyleSheet("QLabel { background-color : green }");
    }
    else {
        ui->labelProximityBinLoadStatus->setStyleSheet("QLabel { background-color : red }");
    }
}
void GroupBoxLiftUpDown::setLiftUpButtonState()
{
    if (relayBinLiftUp->isDeviceStateLOW()) {
        ui->pushButtonLiftUp->setText("ON");
        //ui->pushButtonLiftUp->setStyleSheet("QPushButton { background-color : green }");
    }
    else {
        ui->pushButtonLiftUp->setText("OFF");
        //ui->pushButtonLiftUp->setStyleSheet("QPushButton { background-color : red }");
    }
}
void GroupBoxLiftUpDown::setLiftDownButtonState()
{
    if (relayBinLiftDown->isDeviceStateLOW()) {
        ui->pushButtonLiftDown->setText("ON");
        //ui->pushButtonLiftDown->setStyleSheet("QPushButton { background-color : green }");
    }
    else {
        ui->pushButtonLiftDown->setText("OFF");
        //ui->pushButtonLiftDown->setStyleSheet("QPushButton { background-color : red }");
    }
}
void GroupBoxLiftUpDown::onUpdateIODevices(const QVector<IODevice *> &iodeviceList)
{
    for (auto iodevice : iodeviceList) {
        if (iodevice->getId() == proximityBinLoad->getId()) {
            proximityBinLoad->setDeviceState(iodevice->getDeviceState());
        }
        else if (iodevice->getId() == relayBinLiftUp->getId()) {
            relayBinLiftUp->setDeviceState(iodevice->getDeviceState());
        }
        else if (iodevice->getId() == relayBinLiftDown->getId()) {
            relayBinLiftDown->setDeviceState(iodevice->getDeviceState());
        }
    }

    if (!iodeviceList.empty()) {
        setLiftDownButtonState();
        setLiftUpButtonState();
        setProximityBinLoadStatusLabel();
    }
}

