#include "ProximityTreeWidget.h"
#include "ui_proximitytreewidget.h"
#include <BsfWidgetEnum.h>
#include <QStringList>
#include <iodevicerepo.h>

ProximityTreeWidget::ProximityTreeWidget() :
    ui(new Ui::ProximityTreeWidget) {
  ui->setupUi(this);

  QVariant formId = WIDGET_TYPES::TREEWIDGET_PROXITY_STATUS;
  this->setProperty("formId", formId);

  initForm();
}

void ProximityTreeWidget::initForm() {
  QStringList headers;
  headers.append("ID");
  headers.append("Type");
  headers.append("Status");
  headers.append("Proximity");

  IODeviceRepository ioDeviceRepository;
  proximityWidgetList = ioDeviceRepository.getIODeviceTreeWidgets(IODeviceType::DETECTIONSENSOR);

  ui->treeWidget->setHeaderLabels(headers);
  ui->treeWidget->setColumnHidden(0, true);
  ui->treeWidget->setColumnHidden(1, true);
  ui->treeWidget->insertTopLevelItems(0, proximityWidgetList);
}

void ProximityTreeWidget::onUpdateIODevices(const QVector<IODevice *> &iodeviceList) {
  for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
    const auto treeWidgetItem = ui->treeWidget->topLevelItem(i);
    QVariant id = treeWidgetItem->data(0, Qt::UserRole);

    for (const auto iodevice : iodeviceList) {
      if (iodevice->getId() == id.toInt()) {

        if (iodevice->isDeviceOn()) {
          treeWidgetItem->setIcon(2, materialRegular.visibilityIcon());
        } else {
          treeWidgetItem->setIcon(2, materialRegular.visibilityOffIcon());
        }

        break;
      }
    }
  }
}
