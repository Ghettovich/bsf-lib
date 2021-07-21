#ifndef BSF_IODEVICEREPO_H
#define BSF_IODEVICEREPO_H

#include "iodevice.h"
#include "iodevicetype.h"

#include <QObject>
#include <QVector>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <database/DatabaseService.h>

class IODeviceRepository : public QObject {
 Q_OBJECT

 public:
  explicit IODeviceRepository(std::shared_ptr<service::DatabaseService> &databaseService, QObject *parent);
  QVector<IODevice *> findAllDevices();

 private:
  std::shared_ptr<service::DatabaseService> databaseService;
  IODevice *createDeviceFromQuery(QSqlQuery &query, int deviceTypeId);
};

#endif //BSF_IODEVICEREPO_H
