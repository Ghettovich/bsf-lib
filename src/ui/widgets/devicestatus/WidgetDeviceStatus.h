
#ifndef WIDGETDEVICESTATUS_H
#define WIDGETDEVICESTATUS_H

#include <iodevice.h>
#include <QVector>

class WidgetDeviceStatus
{
public:
    virtual void onUpdateIODevices(const QVector<IODevice *> &iodeviceList) = 0;
};


#endif //WIDGETDEVICESTATUS_H
