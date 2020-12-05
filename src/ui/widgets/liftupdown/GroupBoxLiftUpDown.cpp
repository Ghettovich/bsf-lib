#include "ui_groupboxliftupdown.h"
#include "GroupBoxLiftUpDown.h"
#include <relay.h>
#include <transformpayload.h>

GroupBoxLiftUpDown::GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f)
    :
    QWidget(parent, f), ui(new Ui::GroupBoxLiftUpDown)
{
    ui->setupUi(this);

    relayBinLiftUp = new Relay(30, IODevice::LOW);
    relayBinLiftDown = new Relay(31, IODevice::LOW);

    init();
}
GroupBoxLiftUpDown::GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f, MqttClient *_m_client)
    :
    QWidget(parent, f), ui(new Ui::GroupBoxLiftUpDown), m_client(_m_client)
{
    ui->setupUi(this);

    relayBinLiftDown = new Relay(31, IODevice::LOW);
    relayBinLiftUp = new Relay(30, IODevice::LOW);
    proximityBinLoad = new DetectionSensor(11, IODevice::HIGH);

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
    connect(ui->pushButtonLiftDown, &QPushButton::clicked,
            this, &GroupBoxLiftUpDown::onClickPushButtonLiftDown);

    connect(ui->pushButtonLiftUp, &QPushButton::clicked,
            this, &GroupBoxLiftUpDown::onClickPushButtonLiftUp);
}
void GroupBoxLiftUpDown::onUpdateMessage(const QMqttMessage &msg)
{
    TransformPayload parser;
    QVector<IODevice *> proximities = parser.parseProximitySensors(msg.payload());

    for(const auto sensor : proximities) {
        if(sensor->getId() == proximityBinLoad->getId()) {
            proximityBinLoad->setDeviceState(sensor->getDeviceState());
            break;
        }
    }

    setProximityBinLoadStatusLabel();
    //qDebug() << "Proximities = " << msg.payload();
}
void GroupBoxLiftUpDown::onUpdateStatus(QMqttSubscription::SubscriptionState state)
{
    switch (state) {
        case QMqttSubscription::Unsubscribed:
            qDebug() << (QLatin1String("Unsubscribed"));
            break;
        case QMqttSubscription::SubscriptionPending:
            qDebug() << (QLatin1String("Pending"));
            break;
        case QMqttSubscription::Subscribed:
            qDebug() << (QLatin1String("Subscribed"));
            break;
        case QMqttSubscription::Error:
            qDebug() << (QLatin1String("Error"));
            break;
        default:
            qDebug() << (QLatin1String("--Unknown--"));
            break;
    }
}
void GroupBoxLiftUpDown::onUpdateMessageRelayStates(const QMqttMessage &msg)
{
    qDebug() << "Relays = " << msg.payload();
}
void GroupBoxLiftUpDown::onUpdateStatusRelayStates(QMqttSubscription::SubscriptionState state)
{
    switch (state) {
        case QMqttSubscription::Unsubscribed:
            qDebug() << (QLatin1String("Unsubscribed"));
            break;
        case QMqttSubscription::SubscriptionPending:
            qDebug() << (QLatin1String("Pending"));
            break;
        case QMqttSubscription::Subscribed:
            qDebug() << (QLatin1String("Subscribed"));
            break;
        case QMqttSubscription::Error:
            qDebug() << (QLatin1String("Error"));
            break;
        default:
            qDebug() << (QLatin1String("--Unknown--"));
            break;
    }
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
void GroupBoxLiftUpDown::setProximityBinLoadSubscription(QMqttSubscription *sub)
{
    proximitySub = sub;
    onUpdateStatus(proximitySub->state());
    connect(proximitySub, &QMqttSubscription::messageReceived,
            this, &GroupBoxLiftUpDown::onUpdateMessage);
    connect(proximitySub, &QMqttSubscription::stateChanged,
            this, &GroupBoxLiftUpDown::onUpdateStatus);
    connect(proximitySub, &QMqttSubscription::qosChanged, [this](quint8 qos)
    {
        qDebug() << (QString::number(qos));
    });

    qDebug() << "Created subscription";
}
void GroupBoxLiftUpDown::setRelayStateSubscription(QMqttSubscription *sub)
{
    relayStateSub = sub;
    onUpdateStatusRelayStates(relayStateSub->state());
    connect(relayStateSub, &QMqttSubscription::messageReceived,
            this, &GroupBoxLiftUpDown::onUpdateMessageRelayStates);
    connect(relayStateSub, &QMqttSubscription::stateChanged,
            this, &GroupBoxLiftUpDown::onUpdateStatusRelayStates);
    connect(relayStateSub, &QMqttSubscription::qosChanged, [this](quint8 qos)
    {
        qDebug() << (QString::number(qos));
    });

    qDebug() << "Created relay subscription";
}
void GroupBoxLiftUpDown::setProximityBinLoadStatusLabel()
{
    if(proximityBinLoad->getDeviceState() == IODevice::HIGH) {
        ui->labelProximityBinLoadStatus->setStyleSheet("QLabel { background-color : red }");
    } else if(proximityBinLoad->getDeviceState() == IODevice::LOW) {
        ui->labelProximityBinLoadStatus->setStyleSheet("QLabel { background-color : green }");
    }
}

