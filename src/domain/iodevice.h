#ifndef BSF_IODEVICE_H
#define BSF_IODEVICE_H

#include "action.h"
#include "iodevicetype.h"
#include "recipe.h"
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
  IODeviceType getIoDeviceType() const;
  void setIoDeviceType(const IODeviceType &_ioDeviceType);
  IO_DEVICE_HIGH_LOW getDeviceState() const;
  void setDeviceState(IO_DEVICE_HIGH_LOW _deviceState);

  virtual bool isDeviceStateLOW() const = 0;
  virtual bool isDeviceOn() const = 0;

 private:
  int id = 0;
  QString description;
  Arduino *arduino;
  Action action;
  IODeviceType ioDeviceType;
  Recipe recipe;

 protected:
  IO_DEVICE_HIGH_LOW deviceState;
};

#endif // IODEVICE_H
