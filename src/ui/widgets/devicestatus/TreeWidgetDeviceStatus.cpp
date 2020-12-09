#include "ui_treewidgetdevicestatus.h"
#include "TreeWidgetDeviceStatus.h"

TreeWidgetDeviceStatus::TreeWidgetDeviceStatus(const QStringList &_headers, const QList<QTreeWidgetItem *> &_treeWidgets)
        :
        headers(_headers), treeWidgets(_treeWidgets), ui(new Ui::TreeWidgetDeviceStatus) {
    ui->setupUi(this);
    initForm();
}

void TreeWidgetDeviceStatus::initForm() {
    ui->treeWidget->setHeaderLabels(headers);
    ui->treeWidget->setColumnHidden(0, true);
    ui->treeWidget->insertTopLevelItems(0, treeWidgets);
}
void TreeWidgetDeviceStatus::onUpdateIODevices(const QVector<IODevice *> &iodeviceList)
{


    for(auto treeItem : treeWidgets) {
        QVariant id(treeItem->data(0, Qt::UserRole));

        // ToDo:: add hashmap off iodevices, check with contains and update

        qDebug() << "var. id = " << id.toString();
    }
}


