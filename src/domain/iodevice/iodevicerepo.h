#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include "iodevice.h"
#include "iodevicetype.h"

#include <QObject>
#include <database/DatabaseService.h>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class IODeviceRepository : public QObject {
  Q_OBJECT

 public:
  explicit IODeviceRepository(std::shared_ptr<service::DatabaseService>& databaseService, QObject *parent);
//  IODeviceType getIODeviceType(int ioDeviceTyperId);
//  QVector<IODeviceType> getArduinoIODeviceTypes(int id);
  QVector<IODevice *> getIODeviceList(IODeviceType::IO_DEVICE_TYPE ioDeviceType);
//  QVector<IODevice *> getArduinoIODeviceList(int arduinoId, int ioDeviceTypeId, IODeviceType::IO_DEVICE_TYPE);
//  QList<QTreeWidgetItem *> getIODeviceTreeWidgets(IODeviceType::IO_DEVICE_TYPE ioDeviceType);

 private:
  std::shared_ptr<service::DatabaseService> databaseService;
  void createRelayList(QSqlQuery &, QVector<IODevice *> &);
  void createWeightSensorList(QSqlQuery &, QVector<IODevice *> &);
  void createDetectionSensorList(QSqlQuery &, QVector<IODevice *> &);
};

#endif //BSF_IODEVICEREPO_H
