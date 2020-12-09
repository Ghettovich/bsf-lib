#include "ui_groupboxbinloaddrop.h"
#include "GroupBoxBinLoadDrop.h"
#include <BsfWidgetEnum.h>

GroupBoxBinLoadDrop::GroupBoxBinLoadDrop(QWidget *parent, const Qt::WindowFlags &f, MqttClient *_m_client)
    :
    QWidget(parent, f), ui(new Ui::GroupBoxBinLoadDrop), m_client(_m_client)
{
    ui->setupUi(this);
    QVariant formId = WIDGET_TYPES::GROUPBOX_BIN_LOAD_DROP;
    this->setProperty("formId", formId);

    relayBinLoad = new Relay(32, IODevice::LOW); // Digital
    relayBinDrop = new Relay(33, IODevice::LOW); // Digital
    proximityBinDrop = new DetectionSensor(10, IODevice::HIGH); // PULL UP (HIGH = OFF!)

    init();
}
GroupBoxBinLoadDrop::~GroupBoxBinLoadDrop()
{
    delete ui;
}
void GroupBoxBinLoadDrop::init()
{
    ui->labelProximityBinDropStatus->setText("");
    setProximityBinDropLabelStatus();
    setBinLoadButtonState();
    setBinDropButtonState();

    connect(ui->pushButtonBinLoadRelay, &QPushButton::clicked,
            this, &GroupBoxBinLoadDrop::onClickPushButtonBinLoad);
    connect(ui->pushButtonBinDropRelay, &QPushButton::clicked,
            this, &GroupBoxBinLoadDrop::onClickPushButtonBinDrop);
}
void GroupBoxBinLoadDrop::setProximityBinDropLabelStatus()
{
    if (proximityBinDrop->isDeviceStateLOW()) {
        ui->labelProximityBinDropStatus->setStyleSheet("QLabel { background-color : green }");
    }
    else {
        ui->labelProximityBinDropStatus->setStyleSheet("QLabel { background-color : red }");
    }
}
void GroupBoxBinLoadDrop::setBinLoadButtonState()
{
    if (relayBinLoad->isDeviceStateLOW()) {
        ui->pushButtonBinLoadRelay->setText("OFF");
        ui->pushButtonBinLoadRelay->setStyleSheet("QPushButton { background-color : green }");
    }
    else {
        ui->pushButtonBinLoadRelay->setText("ON");
        ui->pushButtonBinLoadRelay->setStyleSheet("QPushButton { background-color : red }");
    }
}
void GroupBoxBinLoadDrop::setBinDropButtonState()
{
    if (relayBinDrop->isDeviceStateLOW()) {
        ui->pushButtonBinDropRelay->setText("OFF");
        ui->pushButtonBinDropRelay->setStyleSheet("QPushButton { background-color : green }");
    }
    else {
        ui->pushButtonBinDropRelay->setText("ON");
        ui->pushButtonBinDropRelay->setStyleSheet("QPushButton { background-color : red }");
    }
}
void GroupBoxBinLoadDrop::onClickPushButtonBinLoad()
{
    QJsonObject jsonPayload;
    jsonPayload["toggle"] = relayBinLoad->getId();

    m_client->publish(toggleRelayTopic, jsonPayload);
}
void GroupBoxBinLoadDrop::onClickPushButtonBinDrop()
{
    QJsonObject jsonPayload;
    jsonPayload["toggle"] = relayBinDrop->getId();

    m_client->publish(toggleRelayTopic, jsonPayload);
}
void GroupBoxBinLoadDrop::onUpdateIODevices(const QVector<IODevice *> &iodeviceList)
{
    for (auto iodevice : iodeviceList) {
        if (iodevice->getId() == proximityBinDrop->getId()) {
            proximityBinDrop->setDeviceState(iodevice->getDeviceState());
        }
        else if (iodevice->getId() == relayBinLoad->getId()) {
            relayBinLoad->setDeviceState(iodevice->getDeviceState());
        }
        else if (iodevice->getId() == relayBinDrop->getId()) {
            relayBinDrop->setDeviceState(iodevice->getDeviceState());
        }
    }

    if (!iodeviceList.empty()) {
        setBinDropButtonState();
        setBinLoadButtonState();
        setProximityBinDropLabelStatus();
    }
}
