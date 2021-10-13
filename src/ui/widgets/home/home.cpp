#include "ui_home.h"
#include "home.h"

#include <QListWidgetItem>

using namespace appservice;

Home::Home(std::shared_ptr<IODeviceAppService> &_deviceAppService, QWidget *parent) :
    ui(new Ui::Home),
    deviceAppService(_deviceAppService),
    QWidget(parent) {
  ui->setupUi(this);

  auto deviceList = deviceAppService->findAll(IODeviceType::DETECTIONSENSOR);

  for (const auto &device: deviceList) {
    QString text = QString("%1 OFF").arg(device->getDescription());
    auto listWidgetItem = new QListWidgetItem(text);
    listWidgetItem->setData(Qt::UserRole, device->getId());
    ui->listWidgetProximities->addItem(listWidgetItem);
  }

  deviceList = deviceAppService->findAll(IODeviceType::RELAY);

  for (const auto &device: deviceList) {
    QString text = QString("%1 OFF").arg(device->getDescription());
    auto listWidgetItem = new QListWidgetItem(text);
    listWidgetItem->setData(Qt::UserRole, device->getId());
    ui->listWidgetRelays->addItem(listWidgetItem);
  }

  QObject::connect(deviceAppService.get(), &IODeviceAppService::updateIODeviceState,
                   this, &Home::onUpdateProximities);
  QObject::connect(deviceAppService.get(), &IODeviceAppService::updateIODeviceState,
                   this, &Home::onUpdateRelays);

}
Home::~Home() {
  delete ui;
}
void Home::onUpdateProximities(int deviceId, bool status) {

  for (int i = 0; i < ui->listWidgetProximities->count(); i++) {
    const auto listWidgetItem = ui->listWidgetProximities->item(i);
    QVariant id = listWidgetItem->data(Qt::UserRole);

    if (deviceId == id.toInt()) {

      auto device = deviceAppService->findOne(deviceId);

      QString text = QString("%1 %2").arg(device->getDescription(), (status ? "ON" : "OFF"));
      listWidgetItem->setText(text);

      qDebug() << "updated proximity";
      break;
    }
  }
}
void Home::onUpdateRelays(int deviceId, bool status) {
  for (int i = 0; i < ui->listWidgetRelays->count(); i++) {
    const auto listWidgetItem = ui->listWidgetRelays->item(i);
    QVariant id = listWidgetItem->data(Qt::UserRole);

    if (deviceId == id.toInt()) {

      auto device = deviceAppService->findOne(deviceId);

      QString text = QString("%1 %2").arg(device->getDescription(), (status ? "ON" : "OFF"));
      listWidgetItem->setText(text);

      qDebug() << "updated relay";
      break;
    }
  }
}
