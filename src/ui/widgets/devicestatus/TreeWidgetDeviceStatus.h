#ifndef BSF_LIB_TREEWIDGETDEVICESTATUS_H
#define BSF_LIB_TREEWIDGETDEVICESTATUS_H

namespace Ui {
    class TreeWidgetDeviceStatus;
}

#include <iodevice.h>
#include <QObject>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QWidget>

class TreeWidgetDeviceStatus : public QWidget {

    Q_OBJECT

public:
    TreeWidgetDeviceStatus(const QStringList &headers, const QList<QTreeWidgetItem *> &treeWidgets);
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList);

private:
    const QStringList &headers;
    const QList<QTreeWidgetItem *> &treeWidgets;
    Ui::TreeWidgetDeviceStatus *ui = nullptr;

    void initForm();
};


#endif //BSF_LIB_TREEWIDGETDEVICESTATUS_H
