#include "iodevicetype.h"
#include <QMetaEnum>

IODeviceType::IODeviceType(int id)
    :
    id(id)
{
    ioDeviceType = (IO_DEVICE_TYPE(id));
}

int IODeviceType::getId() const
{
    return id;
}

QString IODeviceType::getType() const
{
    return type;
}

void IODeviceType::setType(const QString &_type)
{
    type = _type;
}

QString IODeviceType::getDescription() const
{
    return description;
}

void IODeviceType::setDescription(const QString &_description)
{
    description = _description;
}

IODeviceType::IO_DEVICE_TYPE IODeviceType::getIODeviceType()
{
    return ioDeviceType;
}

void IODeviceType::setIODeviceType(IO_DEVICE_TYPE _type)
{
    ioDeviceType = _type;
}

void IODeviceType::identifyIODeviceTypeEnum(IODeviceType &ioDeviceType)
{
    if (ioDeviceType.getId() == relayTypeId) {
        ioDeviceType.setIODeviceType(IODeviceType::RELAY);
    }
    else if (ioDeviceType.getId() == weightSensorTypeId) {
        ioDeviceType.setIODeviceType(IODeviceType::WEIGHTSENSOR);
    }
    else if (ioDeviceType.getId() == detectionSensorTypeId) {
        ioDeviceType.setIODeviceType(IODeviceType::DETECTIONSENSOR);
    }
    else {
        printf("\nUnknown device type from database");
    }
}
