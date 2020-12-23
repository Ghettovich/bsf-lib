#include <ui/mqttsubscription/SubscriptionWindow.h>
#include "ui_operatormqttclient.h"
#include "OperatorMqttClient.h"

OperatorMqttClient::OperatorMqttClient(QWidget *parent, const Qt::WindowFlags &f)
    : QWidget(parent, f), ui(new Ui::OperatorMqttClient)
{
    ui->setupUi(this);

    connect(ui->pushButtonConnect, &QPushButton::clicked, this, &OperatorMqttClient::onPushButtonConnectClicked);
    connect(ui->pushButtonPublish, &QPushButton::clicked, this, &OperatorMqttClient::onPushButtonPublishClicked);
    connect(ui->pushButtonSubscribe, &QPushButton::clicked, this, &OperatorMqttClient::onPushButtonSubscribeClicked);

    m_client = new QMqttClient(this);
    m_client->setHostname("localhost");
    m_client->setPort(1883);
    m_client->connectToHost();

    connect(m_client, &QMqttClient::stateChanged, this, &OperatorMqttClient::onUpdateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &OperatorMqttClient::onBrokerDisconnected);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
            + QLatin1String(" Received Topic: ")
            + topic.name()
            + QLatin1String(" Message: ")
            + message
            + QLatin1Char('\n');
        ui->textEdit->insertPlainText(content);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
            + QLatin1String(" PingResponse")
            + QLatin1Char('\n');
        ui->textEdit->insertPlainText(content);
    });
}
OperatorMqttClient::~OperatorMqttClient()
{
    delete ui;
}
void OperatorMqttClient::onUpdateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(": State Change")
        + QString::number(m_client->state())
        + QLatin1Char('\n');
    ui->textEdit->insertPlainText(content);
}
void OperatorMqttClient::onBrokerDisconnected()
{
    ui->lineEditHost->setEnabled(true);
    ui->lineEditPort->setEnabled(true);
    ui->pushButtonConnect->setText(tr("Connect"));
}
void OperatorMqttClient::onPushButtonConnectClicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->lineEditHost->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        ui->pushButtonConnect->setText(tr("Disconnect"));
        m_client->connectToHost();
    } else {
        ui->lineEditHost->setEnabled(true);
        ui->lineEditPort->setEnabled(true);
        ui->pushButtonConnect->setText(tr("Connect"));
        m_client->disconnectFromHost();
    }
}
void OperatorMqttClient::onPushButtonSubscribeClicked()
{
    auto subscription = m_client->subscribe(ui->lineEditTopic->text(), ui->spinBoxSubscriptionQos->text().toUInt());
    if (!subscription) {
        qDebug() << "Could not subscribe. Is there a valid connection?";
        return;
    }
    auto subWindow = new SubscriptionWindow(subscription);
    subWindow->setWindowTitle(subscription->topic().filter());
    subWindow->show();
}
void OperatorMqttClient::onPushButtonPublishClicked()
{
    if (m_client->publish(ui->lineEditTopic->text(),
                          ui->lineEditMessage->text().toUtf8(),
                          ui->spinBoxMessageQos->text().toUInt(),
                          ui->checkBoxRetain->isChecked()) == -1)
        qDebug() << "Could not publish message";
}
