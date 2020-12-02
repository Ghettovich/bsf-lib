#include "ui_groupboxliftupdown.h"
#include "GroupBoxLiftUpDown.h"
#include <relay.h>

GroupBoxLiftUpDown::GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f)
    :
    QWidget(parent, f), ui(new Ui::GroupBoxLiftUpDown)
{
    ui->setupUi(this);

    relayBinLiftDown = new Relay(0, IODevice::LOW);
    relayBinLiftUp = new Relay(0, IODevice::LOW);

    init();
}
GroupBoxLiftUpDown::GroupBoxLiftUpDown(QWidget *parent, const Qt::WindowFlags &f, MqttClient *_m_client)
    :
    QWidget(parent, f), ui(new Ui::GroupBoxLiftUpDown), m_client(_m_client)
{
    ui->setupUi(this);

    relayBinLiftDown = new Relay(0, IODevice::LOW);
    relayBinLiftUp = new Relay(0, IODevice::LOW);

    init();
}

GroupBoxLiftUpDown::~GroupBoxLiftUpDown()
{
    if(!m_sub) {
        m_sub->unsubscribe();
    }
    delete ui;
}

void GroupBoxLiftUpDown::init()
{
    connect(ui->pushButtonLiftDown, &QPushButton::clicked,
            this, &GroupBoxLiftUpDown::onClickPushButtonLiftDown);

    connect(ui->pushButtonLiftUp, &QPushButton::clicked,
            this, &GroupBoxLiftUpDown::onClickPushButtonLiftUp);
}
void GroupBoxLiftUpDown::onUpdateMessage(const QMqttMessage &msg)
{
    qDebug() << msg.payload();
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
void GroupBoxLiftUpDown::onClickPushButtonLiftDown()
{
    m_client->publish("toggle/relay", "he ho lets go!!");
    printf("\ndown clicked");
}
void GroupBoxLiftUpDown::onClickPushButtonLiftUp()
{
    m_client->publish("toggle/relay", "he ho lets go!!");
    printf("\nUp clicked");
}
void GroupBoxLiftUpDown::setProximityBinLoadSubscription(QMqttSubscription *sub)
{
    m_sub = sub;
    onUpdateStatus(m_sub->state());
    connect(m_sub, &QMqttSubscription::messageReceived, this, &GroupBoxLiftUpDown::onUpdateMessage);
    connect(m_sub, &QMqttSubscription::stateChanged, this, &GroupBoxLiftUpDown::onUpdateStatus);
    connect(m_sub, &QMqttSubscription::qosChanged, [this](quint8 qos)
    {
        qDebug() << (QString::number(qos));
    });

    qDebug() << "Created subscription";
}

