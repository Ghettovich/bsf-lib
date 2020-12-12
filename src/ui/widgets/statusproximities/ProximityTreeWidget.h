#ifndef PROXIMITYTREEWIDGET_H
#define PROXIMITYTREEWIDGET_H

namespace Ui {
class ProximityTreeWidget;
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

class ProximityTreeWidget: public IOWidgetStatusInterface {

Q_OBJECT
//Q_PLUGIN_METADATA(IID "plugins.IOWidgetStatusInterface_iid")
Q_INTERFACES(IOWidgetStatusInterface)

public:
    ProximityTreeWidget(const QStringList &headers, const QList<QTreeWidgetItem *> &treeWidgets);

public slots:
    void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) override;

private:
    const QStringList &headers;
    const QList<QTreeWidgetItem *> &treeWidgets;
    Ui::ProximityTreeWidget *ui = nullptr;
    MaterialRegular materialRegular;
    void initForm();
};


#endif //PROXIMITYTREEWIDGET_H
