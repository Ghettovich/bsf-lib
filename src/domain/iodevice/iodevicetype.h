#ifndef BSF_IODEVICETYPE_H
#define BSF_IODEVICETYPE_H

#include <QObject>
#include <QString>

class IODeviceType {

 Q_GADGET;

 public:
  enum IO_DEVICE_TYPE {
    UNKOWN = 0, WEIGHTSENSOR = 1, DETECTIONSENSOR = 2, RELAY = 3, ARDUINO = 4
  };

  Q_ENUM(IO_DEVICE_TYPE);

  explicit IODeviceType(int id = 0);
  int getId() const;
  QString getType() const;
  void setType(const QString &);
  QString getDescription() const;
  void setDescription(const QString &);
  IO_DEVICE_TYPE getIODeviceType();
  void setIODeviceType(IO_DEVICE_TYPE);
  static void identifyIODeviceTypeEnum(IODeviceType &);

 private:
  int id;
  QString type;
  QString description;
  IO_DEVICE_TYPE ioDeviceType;
  const static int weightSensorTypeId = 1, detectionSensorTypeId = 2, relayTypeId = 3;
};

#endif //BSF_IODEVICETYPE_H
