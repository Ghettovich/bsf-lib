
#ifndef IOWIDGETSTATUSINTERFACE_H
#define IOWIDGETSTATUSINTERFACE_H

#include <iodevice.h>
#include <QVector>
#include <QWidget>
#include <QtPlugin>
#include <weightcensor.h>

class IOWidgetStatusInterface : public QWidget {
 Q_OBJECT

 public:
  virtual void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) = 0;
};

#define IOWidgetStatusInterface_iid "plugins.IOWidgetStatusInterface"

Q_DECLARE_INTERFACE(IOWidgetStatusInterface, IOWidgetStatusInterface_iid)

#endif //IOWIDGETSTATUSINTERFACE_H
