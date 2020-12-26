#include "ProximityTreeWidget.h"
#include "ui_proximitytreewidget.h"
#include <BsfWidgetEnum.h>

ProximityTreeWidget::ProximityTreeWidget(const QStringList &_headers,
                                         const QList<QTreeWidgetItem *> &_treeWidgets)
    :
    headers(_headers), treeWidgets(_treeWidgets), ui(new Ui::ProximityTreeWidget) {
  ui->setupUi(this);

  QVariant formId = WIDGET_TYPES::TREEWIDGET_PROXITY_STATUS;
  this->setProperty("formId", formId);

  initForm();
}

void ProximityTreeWidget::initForm() {
  ui->treeWidget->setHeaderLabels(headers);
  ui->treeWidget->setColumnHidden(0, true);
  ui->treeWidget->setColumnHidden(1, true);
  ui->treeWidget->insertTopLevelItems(0, treeWidgets);
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
