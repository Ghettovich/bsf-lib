#ifndef PROXIMITYTREEWIDGET_H
#define PROXIMITYTREEWIDGET_H

namespace Ui {
class ProximityTreeWidget;
}

#include <iodevice.h>
#include <ui/widgets/interfaces/IOWidgetStatusInterface.h>
#include <QObject>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QWidget>
#include <fonts/MaterialRegular.h>

class ProximityTreeWidget : public IOWidgetStatusInterface {

 Q_OBJECT
  Q_INTERFACES(IOWidgetStatusInterface)

 public:
  explicit ProximityTreeWidget();

 public slots:
  void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) override;

 private:
  QList<QTreeWidgetItem *> proximityWidgetList;
  Ui::ProximityTreeWidget *ui = nullptr;
  MaterialRegular materialRegular;
  void initForm();
};

#endif //PROXIMITYTREEWIDGET_H
