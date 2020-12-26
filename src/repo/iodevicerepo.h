#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include <bsfdatabaseconfig.h>
#include <iodevice.h>
#include <iodevicetype.h>
#include <QVector>
#include <QList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtWidgets/QTreeWidgetItem>

class IODeviceRepository {

 public:
  explicit IODeviceRepository(const QString &connection = "");
  IODeviceType getIODeviceType(int ioDeviceTyperId);
  QVector<IODeviceType> getArduinoIODeviceTypes(int id);
  QVector<IODevice *> getArduinoIODeviceList(int arduinoId, int ioDeviceTypeId, IODeviceType::IO_DEVICE_TYPE);
  QList<QTreeWidgetItem *> getIODeviceTreeWidgets(IODeviceType::IO_DEVICE_TYPE ioDeviceType);

 private:
  BsfDbconfig bsfDbConfig;
  void createRelayList(QSqlQuery &, QVector<IODevice *> &);
  void createWeightSensorList(QSqlQuery &, QVector<IODevice *> &);
  void createDetectionSensorList(QSqlQuery &, QVector<IODevice *> &);
};

#endif //BSF_IODEVICEREPO_H
