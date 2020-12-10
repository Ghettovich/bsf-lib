#ifndef RELAYTREEWIDGET_H
#define RELAYTREEWIDGET_H

namespace Ui {
class RelayTreeWidget;
}

#include <iodevice.h>
#include <widgets/devicestatus/WidgetDeviceStatus.h>
#include <QMap>
#include <QObject>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QWidget>
#include <fonts/MaterialRegular.h>

class RelayTreeWidget: public QWidget, public WidgetDeviceStatus {

Q_OBJECT

public:
    RelayTreeWidget(const QStringList &headers, const QList<QTreeWidgetItem *> &treeWidgets);

public slots:
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) override;

private:
    const QStringList &headers;
    const QList<QTreeWidgetItem *> &treeWidgets;
    Ui::RelayTreeWidget *ui = nullptr;
    MaterialRegular materialRegular;

    void initForm();
};


#endif //RELAYTREEWIDGET_H
