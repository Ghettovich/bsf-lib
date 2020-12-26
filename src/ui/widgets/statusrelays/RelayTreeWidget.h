#ifndef RELAYTREEWIDGET_H
#define RELAYTREEWIDGET_H

namespace Ui {
class RelayTreeWidget;
}

#include <iodevice.h>
#include <ui/widgets/interfaces/IOWidgetStatusInterface.h>
#include <QMap>
#include <QObject>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QWidget>
#include <fonts/MaterialRegular.h>

class RelayTreeWidget : public IOWidgetStatusInterface {

 Q_OBJECT
  Q_INTERFACES(IOWidgetStatusInterface)

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
