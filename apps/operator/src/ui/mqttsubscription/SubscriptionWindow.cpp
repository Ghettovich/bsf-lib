#include "ui_subscriptionwindow.h"
#include "SubscriptionWindow.h"

SubscriptionWindow::SubscriptionWindow(QMqttSubscription *_m_sub)
    : m_sub(_m_sub), ui(new Ui::SubscriptionWindow) {
  ui->setupUi(this);

  ui->labelSubscriptionDisplay->setText(m_sub->topic().filter());
  ui->labelQosDisplay->setText(QString::number(m_sub->qos()));
  onUpdateStatus(m_sub->state());
  connect(m_sub, &QMqttSubscription::messageReceived, this, &SubscriptionWindow::onUpdateMessage);
  connect(m_sub, &QMqttSubscription::stateChanged, this, &SubscriptionWindow::onUpdateStatus);
  connect(m_sub, &QMqttSubscription::qosChanged, [this](quint8 qos) {
    ui->labelQosDisplay->setText(QString::number(qos));
  });
  connect(ui->pushButtonUnsubscribe, &QAbstractButton::clicked, m_sub, &QMqttSubscription::unsubscribe);
}

SubscriptionWindow::~SubscriptionWindow() {
  m_sub->unsubscribe();
  delete ui;
}

void SubscriptionWindow::onUpdateMessage(const QMqttMessage &msg) {
  ui->listWidget->addItem(msg.payload());
}

void SubscriptionWindow::onUpdateStatus(QMqttSubscription::SubscriptionState state) {
  switch (state) {
    case QMqttSubscription::Unsubscribed:ui->labelStatusDisplay->setText(QLatin1String("Unsubscribed"));
      break;
    case QMqttSubscription::SubscriptionPending:ui->labelStatusDisplay->setText(QLatin1String("Pending"));
      break;
    case QMqttSubscription::Subscribed:ui->labelStatusDisplay->setText(QLatin1String("Subscribed"));
      break;
    case QMqttSubscription::Error:ui->labelStatusDisplay->setText(QLatin1String("Error"));
      break;
    default:ui->labelStatusDisplay->setText(QLatin1String("--Unknown--"));
      break;
  }
}