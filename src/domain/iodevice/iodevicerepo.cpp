#include "iodevicerepo.h"
#include "iodevicetype.h"
#include "detectionsensor.h"
#include "relay.h"
#include "weightcensor.h"

#include <arduino.h>
#include <QtSql/QSqlQueryModel>

IODeviceRepository::IODeviceRepository(std::shared_ptr<service::DatabaseService> &_databaseService, QObject *parent) :
    QObject(parent), databaseService(_databaseService) {

// 1. open database
  QSqlDatabase d = QSqlDatabase::database();

  // 2. run update function with sql create/update/drop queries
  QVector<QVector<QString>> scripts = {
      {
          "CREATE TABLE IF NOT EXISTS io_device ("
          "id	INTEGER, "
          "action_id	INTEGER NOT NULL, "
          "arduino_id	INTEGER NOT NULL, "
          "type_id      INTEGER NOT NULL, "
          "description	TEXT NOT NULL, "
          "PRIMARY KEY(id AUTOINCREMENT) "
          ");"
      }
  };

  databaseService->runScripts(scripts);

  scripts = {
      {
          "CREATE TABLE IF NOT EXISTS io_device_type ("
          "id	INTEGER, "
          "type	TEXT NOT NULL UNIQUE, "
          "description	TEXT, "
          "PRIMARY KEY(id AUTOINCREMENT) "
          ");"
      }
  };

  databaseService->runScripts(scripts);
}

QMap<int, std::shared_ptr<IODevice>> IODeviceRepository::findAllDevices() {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString = "SELECT io.id AS io_id, io.description AS io_desc, io_dev_type.id AS io_dev_type_id "
                        "FROM io_device io "
                        "INNER JOIN io_device_type io_dev_type ON io.type_id = io_dev_type.id; ";

  if (!query.exec(queryString)) {
    qDebug("DB table \"io_device\" findAll, Either select query error or table does not exists!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }

  QMap<int, std::shared_ptr<IODevice>> devices;

  while (query.next()) {
    devices.insert(query.value("io_id").toInt(),
                   createDeviceFromQuery(query, query.value("io_dev_type_id").toInt()));
  }

  return devices;
}

std::shared_ptr<IODevice> IODeviceRepository::createDeviceFromQuery(QSqlQuery &query, int deviceTypeId) {
  std::shared_ptr<IODevice> device = nullptr;

  switch (deviceTypeId) {
    case (int)IODeviceType::RELAY :
      device = std::make_shared<Relay>(query.value("io_id").toInt(), IODevice::HIGH);
      device->setDeviceType(IODeviceType::RELAY);
      break;
    case (int)IODeviceType::WEIGHTSENSOR:
      device = std::make_shared<WeightSensor>(query.value("io_id").toInt(), IODevice::LOW);
      device->setDeviceType(IODeviceType::WEIGHTSENSOR);
      break;
    case (int)IODeviceType::DETECTIONSENSOR:
      device = std::make_shared<DetectionSensor>(query.value("io_id").toInt(), IODevice::HIGH);
      device->setDeviceType(IODeviceType::DETECTIONSENSOR);
      break;
    default:
      qDebug() << "Could not create device from device type id.";
      break;
  }

  device->setDescription(query.value("io_desc").toString());

  return device;
}