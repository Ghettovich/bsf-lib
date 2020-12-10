#include "RelayTreeWidget.h"
#include "ui_relaytreewidget.h"
#include <BsfWidgetEnum.h>

RelayTreeWidget::RelayTreeWidget(const QStringList &_headers,
                                         const QList<QTreeWidgetItem *> &_treeWidgets)
    :
    headers(_headers), treeWidgets(_treeWidgets), ui(new Ui::RelayTreeWidget)
{
    ui->setupUi(this);

    QVariant formId = WIDGET_TYPES::TREEWIDGET_RELAY_STATUS;
    this->setProperty("formId", formId);

    initForm();
}

void RelayTreeWidget::initForm()
{
    ui->treeWidget->setHeaderLabels(headers);
    ui->treeWidget->setColumnHidden(0, true);
    ui->treeWidget->setColumnHidden(1, true);
    ui->treeWidget->insertTopLevelItems(0, treeWidgets);
}
void RelayTreeWidget::onUpdateIODevices(const QVector<IODevice *> &iodeviceList)
{
    qDebug() << "Count = " << ui->treeWidget->topLevelItemCount();

    for (int i =0; i < ui->treeWidget->topLevelItemCount(); i++) {
        const auto treeWidgetItem = ui->treeWidget->topLevelItem(i);
        QVariant id = treeWidgetItem->data(0, Qt::UserRole);

        for (const auto iodevice : iodeviceList) {
            if (iodevice->getId() == id.toInt()) {

                if(iodevice->isDeviceOn()) {
                    treeWidgetItem->setIcon(2, materialRegular.boltIcon(Qt::red));
                }
                else {
                    treeWidgetItem->setIcon(2, materialRegular.boltIcon(Qt::green));
                }

                break;
            }
        }
    }
}
