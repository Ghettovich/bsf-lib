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
        ui->labelProximityBinLoadStatus->setPixmap(materialRegular.visibilityIcon(Qt::lightGray).pixmap(48,48));
    }
    else {
        ui->labelProximityBinLoadStatus->setPixmap(materialRegular.visibilityOffIcon(Qt::darkGray).pixmap(48,48));
    }
}
void GroupBoxLiftUpDown::setLiftUpButtonState()
{
    if (relayBinLiftUp->isDeviceStateLOW()) {
        ui->pushButtonLiftUp->setText("ON");
        ui->pushButtonLiftUp->setIcon(materialRegular.boltIcon(Qt::green));
    }
    else {
        ui->pushButtonLiftUp->setText("OFF");
        ui->pushButtonLiftUp->setIcon(materialRegular.boltIcon(Qt::red));
    }
}
void GroupBoxLiftUpDown::setLiftDownButtonState()
{
    if (relayBinLiftDown->isDeviceStateLOW()) {
        ui->pushButtonLiftDown->setText("ON");
        ui->pushButtonLiftDown->setIcon(materialRegular.boltIcon(Qt::green));
    }
    else {
        ui->pushButtonLiftDown->setText("OFF");
        ui->pushButtonLiftDown->setIcon(materialRegular.boltIcon(Qt::red));
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

