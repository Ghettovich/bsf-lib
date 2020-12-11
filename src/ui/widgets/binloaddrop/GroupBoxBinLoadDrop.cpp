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

    relayBinLoad = new Relay(32, IODevice::HIGH); // Digital
    relayBinDrop = new Relay(33, IODevice::HIGH); // Digital
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
    if (proximityBinDrop->isDeviceOn()) {
        ui->labelProximityBinDropStatus->setPixmap(materialRegular.visibilityIcon(Qt::lightGray).pixmap(48,48));
    }
    else {
        ui->labelProximityBinDropStatus->setPixmap(materialRegular.visibilityOffIcon(Qt::darkGray).pixmap(48,48));
    }
}
void GroupBoxBinLoadDrop::setBinLoadButtonState()
{
    if (!relayBinLoad->isDeviceOn()) {
        ui->pushButtonBinLoadRelay->setIcon(materialRegular.boltIcon(Qt::green));
        ui->pushButtonBinLoadRelay->setText("ON");
    }
    else {
        ui->pushButtonBinLoadRelay->setIcon(materialRegular.boltIcon(Qt::red));
        ui->pushButtonBinLoadRelay->setText("OFF");
    }
}
void GroupBoxBinLoadDrop::setBinDropButtonState()
{
    if (!relayBinDrop->isDeviceOn()) {
        ui->pushButtonBinDropRelay->setIcon(materialRegular.boltIcon(Qt::green));
        ui->pushButtonBinDropRelay->setText("ON");
    }
    else {
        ui->pushButtonBinDropRelay->setIcon(materialRegular.boltIcon(Qt::red));
        ui->pushButtonBinDropRelay->setText("OFF");
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
