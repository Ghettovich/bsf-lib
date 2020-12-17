#ifndef RELAYTREEWIDGET_H
#define RELAYTREEWIDGET_H

namespace Ui {
class RelayTreeWidget;
}

#include <iodevice.h>
#include <widgets/devicestatus/IOWidgetStatusInterface.h>
#include <QMap>
#include <QObject>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QWidget>
#include <fonts/MaterialRegular.h>

class RelayTreeWidget: public IOWidgetStatusInterface {

Q_OBJECT
//Q_PLUGIN_METADATA(IID "plugins.IOWidgetStatusInterface")
Q_INTERFACES(IOWidgetStatusInterface)

public:
    RelayTreeWidget(const QStringList &headers, const QList<QTreeWidgetItem *> &treeWidgets);

public slots:
    void onUpdateIODevice(const IODevice *ioDevice) override;
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) override;

private:
    const QStringList &headers;
    const QList<QTreeWidgetItem *> &treeWidgets;
    Ui::RelayTreeWidget *ui = nullptr;
    MaterialRegular materialRegular;

    void initForm();
};


#endif //RELAYTREEWIDGET_H
