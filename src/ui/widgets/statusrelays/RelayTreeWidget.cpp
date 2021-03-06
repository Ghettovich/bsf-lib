#include "RelayTreeWidget.h"
#include "ui_relaytreewidget.h"
#include <BsfWidgetEnum.h>
#include <iodevicerepo.h>

RelayTreeWidget::RelayTreeWidget() :
   ui(new Ui::RelayTreeWidget) {
  ui->setupUi(this);

  QVariant formId = WIDGET_TYPES::TREEWIDGET_RELAY_STATUS;
  this->setProperty("formId", formId);

  initForm();
}

void RelayTreeWidget::initForm() {
  headers.append("ID");
  headers.append("Type");
  headers.append("Status");
  headers.append("Relay");

  IODeviceRepository ioDeviceRepository;
  treeWidgets = ioDeviceRepository.getIODeviceTreeWidgets(IODeviceType::RELAY);

  ui->treeWidget->setHeaderLabels(headers);
  ui->treeWidget->setColumnHidden(0, true);
  ui->treeWidget->setColumnHidden(1, true);
  ui->treeWidget->insertTopLevelItems(0, treeWidgets);
}

void RelayTreeWidget::onUpdateIODevices(const QVector<IODevice *> &iodeviceList) {
  for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
    const auto treeWidgetItem = ui->treeWidget->topLevelItem(i);
    QVariant id = treeWidgetItem->data(0, Qt::UserRole);

    for (const auto iodevice : iodeviceList) {
      if (iodevice->getId() == id.toInt()) {

        if (iodevice->isDeviceOn()) {
          treeWidgetItem->setIcon(2, materialRegular.boltIcon(Qt::green));
        } else {
          treeWidgetItem->setIcon(2, materialRegular.boltIcon(Qt::red));
        }

        break;
      }
    }
  }
}

