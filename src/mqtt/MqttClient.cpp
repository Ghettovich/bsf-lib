#include "MqttClient.h"
#include <BsfWidgetEnum.h>
#include <transformpayload.h>
#include <QString>
#include <QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <ui/widgets/interfaces/IOWidgetStatusInterface.h>
#include <widgets/interfaces/RecipeStatusInterface.h>

MqttClient::MqttClient(QObject *parent)
    : QObject(parent)
{
    m_client = new QMqttClient(this);
    m_client->setHostname("localhost");
    m_client->setPort(1883);

    connect(m_client, &QMqttClient::stateChanged, this, &MqttClient::onStateChanged);
    connect(m_client, &QMqttClient::disconnected, this, &MqttClient::onBrokerDisconnected);
    connect(m_client, &QMqttClient::messageReceived, this, &MqttClient::onMessageReceived);

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]()
    {
        const QString content = QDateTime::currentDateTime().toString()
            + QLatin1String(" PingResponse")
            + QLatin1Char('\n');
        qDebug() << content;
    });
}
QMqttClient::ClientState MqttClient::getClientState() const
{
    return m_client->state();
}
void MqttClient::connectToHost()
{
    if(m_client->state() == QMqttClient::Disconnected &&
        m_client->state() != QMqttClient::Connecting) {
        m_client->connectToHost();
    }
}
void MqttClient::publishToggleRelay(IODevice *iodevice)
{
    quint8 QoS = 1;
    QJsonObject jsonPayload;
    jsonPayload["toggle"] = iodevice->getId();

    doc = QJsonDocument(jsonPayload);

    if (m_client->publish(toggleRelayTopic,
                          doc.toJson(),
                          QoS,
                          false) == -1) {
    }
}
void MqttClient::publishConfirmComponent(const Component &component)
{
    quint8 QoS = 1;
    QJsonObject jsonPayload;
    jsonPayload["recipeId"] = component.getRecipeId();
    jsonPayload["componentId"] = component.getComponentId();
    jsonPayload["confirm"] = true;

    doc = QJsonDocument(jsonPayload);

    if (m_client->publish(configureRecipeTopic,
                          doc.toJson(),
                          QoS,
                          false) == -1) {
    }
}
void MqttClient::publishRecipe(const Recipe& recipe, const Component &component)
{
    quint8 QoS = 1;
    QJsonObject jsonPayloadObject;
    jsonPayloadObject["recipeId"] = recipe.getId();

    if(component.getComponentId() == 0) {
        jsonPayloadObject["componentId"] = recipe.componentList.first().getComponentId();
        jsonPayloadObject["targetWeight"] = recipe.componentList.first().getTargetWeight();
    } else {
        jsonPayloadObject["componentId"] = component.getComponentId();
        jsonPayloadObject["targetWeight"] = component.getTargetWeight();
    }

    doc = QJsonDocument(jsonPayloadObject);

    if (m_client->publish(configureRecipeTopic,
                          doc.toJson(),
                          QoS,
                          false) == -1) {
    }
}
void MqttClient::addIODeviceSubscription(const QString &topic, quint8 QoS, QWidget *widget)
{
    auto subscription = this->subscription(topic);

    if (!subscription) {
        subscription = m_client->subscribe(topic, QoS);
        subscriptionList.append(subscription);

        if (!subscription)
            qDebug() << "Error, could not sub D:!";
    }

    if(!iodeviceWidgetSubscriptionMap.contains(widget->property("formId").toInt())) {
        QStringList subTopicList;
        subTopicList.append(topic);

        iodeviceWidgetSubscriptionMap.insert(widget->property("formId").toInt(), subTopicList);
        createIODeviceWidgetSubscriptions(widget);
    } else {
        iodeviceWidgetSubscriptionMap.find(widget->property("formId").toInt())->append(topic);
    }
}
void MqttClient::addRecipeDataSubscription(quint8 QoS, QWidget *widget)
{
    auto subscription = this->subscription(recipeDataTopic);

    if (!subscription) {
        subscription = m_client->subscribe(recipeDataTopic, QoS);
        subscriptionList.append(subscription);

        if (!subscription)
            qDebug() << "Error, could not sub D:!";
    }

    if(!recipeWidgetSubscriptionMap.contains(widget->property("formId").toInt())) {

        QStringList subTopicList;
        subTopicList.append(recipeDataTopic);

        recipeWidgetSubscriptionMap.insert(widget->property("formId").toInt(), subTopicList);
        createRecipeWidgetSubscriptions(widget);
    }
}
QMqttSubscription *MqttClient::subscription(const QString &topic)
{
    for (const auto sub : subscriptionList) {
        if(sub->topic().match(topic)) {
            return sub;
            qDebug() << "Found matching sub";
        }
    }

    return nullptr;
}
void MqttClient::onBrokerDisconnected()
{
    qDebug() << "Broker disconnected!";
}
void MqttClient::onStateChanged()
{
    qDebug() << "on state changed triggered...";
    switch (m_client->state()) {

        case QMqttClient::Disconnected: {
            const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(": State Change Disconnected ")
                + QString::number(m_client->state())
                + QLatin1Char('\n');
            qDebug() << content;
            break;
        }
        case QMqttClient::Connecting: {
            const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(": State Change Conecting ... ")
                + QString::number(m_client->state())
                + QLatin1Char('\n');
            qDebug() << content;
            break;
        }
        case QMqttClient::Connected: {
            emit brokerConnected();
            const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(": State Change Connected! ")
                + QString::number(m_client->state())
                + QLatin1Char('\n');
            qDebug() << content;
            break;
        }
    }
}
void MqttClient::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    TransformPayload parser;

    if(QString::compare(topic.name(), proximityLiftTopic) == 0 ||
        QString::compare(topic.name(), relayStatesTopic) == 0) {

        QVector<IODevice *> iodeviceList;
        iodeviceList = parser.parseIODevices(message);

        emit newIODeviceStates(iodeviceList);
    } else if(QString::compare(topic.name(), recipeDataTopic) == 0) {

        WeightSensor *weightSensor = parser.parseRecipeData(message);
        emit newDataForScale(weightSensor);
    }

    const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(" Received Topic: ")
        + topic.name()
        + QLatin1String(" Message: ")
        + message
        + QLatin1Char('\n');
    qDebug() << content;
}
void MqttClient::createRecipeWidgetSubscriptions(QWidget *widget)
{
    RecipeStatusInterface *recipeStatusInterface =
        qobject_cast<RecipeStatusInterface*>(widget);

    connect(this, &MqttClient::newDataForScale,
            recipeStatusInterface, &RecipeStatusInterface::onUpdateIODevice);
}

void MqttClient::createIODeviceWidgetSubscriptions(QWidget *widget)
{
    IOWidgetStatusInterface *widgetDeviceStatusInterface =
        qobject_cast<IOWidgetStatusInterface*>(widget);

    connect(this, &MqttClient::newIODeviceStates,
            widgetDeviceStatusInterface, &IOWidgetStatusInterface::onUpdateIODevices);
}
