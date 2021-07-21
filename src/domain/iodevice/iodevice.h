#ifndef BSF_IODEVICE_H
#define BSF_IODEVICE_H

#include "action.h"
#include "iodevicetype.h"

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QJsonObject>

class Arduino;

class IODevice {

 Q_GADGET

 public:
  enum IO_DEVICE_HIGH_LOW {
    LOW, HIGH
  };

  Q_ENUM(IO_DEVICE_HIGH_LOW);

  explicit IODevice(int id = 0);
  IODevice(int id, IO_DEVICE_HIGH_LOW _deviceState);
  int getId() const;
  QString getDescription() const;
  void setDescription(const QString &_description);
  Arduino *getArduino();
  void setArduino(Arduino *_arduino);
  Action getAction() const;
  void setAction(const Action &_action);
  IODeviceType::IO_DEVICE_TYPE getDeviceType();
  void setDeviceType(IODeviceType::IO_DEVICE_TYPE deviceType);
  IO_DEVICE_HIGH_LOW getDeviceState() const;
  void setDeviceState(IO_DEVICE_HIGH_LOW _deviceState);

  virtual bool isDeviceOn() const = 0;

 private:
  int iodeviceId = 0;
  QString description;
  IODeviceType::IO_DEVICE_TYPE deviceType = IODeviceType::IO_DEVICE_TYPE::UNKOWN;

  Arduino *arduino;
  Action action;
  IODeviceType ioDeviceType;

 protected:
  IO_DEVICE_HIGH_LOW deviceState;
};

#endif // BSF_IODEVICE_H
