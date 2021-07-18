#include "ProximityTreeWidget.h"
#include "ui_proximitytreewidget.h"
#include <QListWidgetItem>
#include <QDebug>

using namespace appservice;

ProximityTreeWidget::ProximityTreeWidget(std::shared_ptr<BrokerAppService> &_brokerAppService) :
    ui(new Ui::ProximityTreeWidget), brokerAppService(_brokerAppService) {
  ui->setupUi(this);

  initForm();

  connect(brokerAppService.get(), &BrokerAppService::updateDevicesWithState,
          this, &ProximityTreeWidget::onUpdateIODevices);
}

void ProximityTreeWidget::initForm() {
  auto deviceList = brokerAppService->findAll(IODeviceType::DETECTIONSENSOR);

  for (const auto &device :deviceList) {
    auto listWidgetItem = new QListWidgetItem(materialRegular.visibilityOffIcon(), device->getDescription());
    listWidgetItem->setData(Qt::UserRole, device->getId());
    ui->listWidget->addItem(listWidgetItem);
  }
}

void ProximityTreeWidget::onUpdateIODevices(const QVector<IODevice *> &iodeviceList) {
  qDebug() << iodeviceList.count();

  for (int i = 0; i < ui->listWidget->count(); i++) {
    const auto listWidgetItem = ui->listWidget->item(i);
    QVariant id = listWidgetItem->data(Qt::UserRole);

    for (const auto iodevice : iodeviceList) {
      if (iodevice->getId() == id.toInt()) {

        if (iodevice->isDeviceOn()) {
          listWidgetItem->setIcon(materialRegular.visibilityIcon());
        } else {
          listWidgetItem->setIcon(materialRegular.visibilityOffIcon());
        }

        break;
      }
    }
  }
}
