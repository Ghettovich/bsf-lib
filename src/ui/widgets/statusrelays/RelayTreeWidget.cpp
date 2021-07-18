#include "RelayTreeWidget.h"
#include "ui_relaytreewidget.h"
#include <QListWidgetItem>

using namespace appservice;

RelayTreeWidget::RelayTreeWidget(std::shared_ptr<BrokerAppService> &_brokerAppService) :
    ui(new Ui::RelayTreeWidget), brokerAppService(_brokerAppService) {
  ui->setupUi(this);

  initForm();

  connect(brokerAppService.get(), &BrokerAppService::updateDevicesWithState,
          this, &RelayTreeWidget::onUpdateIODevices);
}

void RelayTreeWidget::initForm() {
  auto deviceList = brokerAppService->findAll(IODeviceType::RELAY);

  for (const auto &device :deviceList) {
    auto listWidgetItem = new QListWidgetItem(materialRegular.boltIcon(Qt::red), device->getDescription());
    listWidgetItem->setData(Qt::UserRole, device->getId());
    ui->listWidget->addItem(listWidgetItem);
  }
}

void RelayTreeWidget::onUpdateIODevices(const QVector<IODevice *> &iodeviceList) {
  for (int i = 0; i < ui->listWidget->count(); i++) {
    const auto treeWidgetItem = ui->listWidget->item(i);
    QVariant id = treeWidgetItem->data(Qt::UserRole);

    for (const auto iodevice : iodeviceList) {
      if (iodevice->getId() == id.toInt()) {

        if (iodevice->isDeviceOn()) {
          treeWidgetItem->setIcon(materialRegular.boltIcon(Qt::green));
        } else {
          treeWidgetItem->setIcon(materialRegular.boltIcon(Qt::red));
        }

        break;
      }
    }
  }
}
