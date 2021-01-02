#include "iodevicerepo.h"
#include <bsfdatabaseconfig.h>
#include <arduino.h>
#include <iodevicetype.h>
#include <detectionsensor.h>
#include <relay.h>
#include <weightcensor.h>
#include <fonts/MaterialRegular.h>
#include <QtSql/QSqlQueryModel>

IODeviceRepository::IODeviceRepository(const QString &connection) {
  if (!connection.isEmpty()) {
    bsfDbConfig.setDatabaseName(connection);
  }
}

IODeviceType IODeviceRepository::getIODeviceType(int ioDeviceTypeId) {
  QString queryString = "SELECT  id, type, description "
                        "FROM io_device_type "
                        "WHERE id =:id";

  try {
    QSqlDatabase db;
    bsfDbConfig.setSqlDatabase(db);
    QSqlQuery query = QSqlQuery(db);

    db.open();
    query.prepare(queryString);
    query.bindValue(":id", ioDeviceTypeId);
    query.exec();

    if (query.first()) {
      IODeviceType ioDeviceType = IODeviceType(query.value("id").toInt());
      ioDeviceType.setType(query.value("type").toString());
      ioDeviceType.setDescription(query.value("description").toString());
      IODeviceType::identifyIODeviceTypeEnum(ioDeviceType);
      return ioDeviceType;
    }

  }
  catch (std::exception &e) {
    printf("\n%s", e.what());
  }

  return IODeviceType(0);
}

QVector<IODeviceType> IODeviceRepository::getArduinoIODeviceTypes(int id) {
  QVector<IODeviceType> ioDeviceTypeList = QVector<IODeviceType>();
  QString queryString = "SELECT io_device_type.id, io_device_type.type "
                        "FROM io_device_type INNER JOIN io_device ON io_device.type_id = io_device_type.id "
                        "WHERE io_device.arduino_id =:id "
                        "GROUP BY io_device_type.id, io_device_type.type ";

  try {
    QSqlDatabase db;
    bsfDbConfig.setSqlDatabase(db);
    QSqlQuery query(db);

    db.open();
    query.prepare(queryString);
    query.bindValue(":id", id);

    query.exec();

    while (query.next()) {
      IODeviceType ioDeviceType = IODeviceType(query.value("id").toInt());
      ioDeviceType.setType(query.value("type").toString());
      IODeviceType::identifyIODeviceTypeEnum(ioDeviceType);
      ioDeviceTypeList.append(ioDeviceType);
    }

    db.close();
  }
  catch (std::exception &e) {
    printf("\n%s", e.what());
  }

  return ioDeviceTypeList;
}

QList<QTreeWidgetItem *> IODeviceRepository::getIODeviceTreeWidgets(IODeviceType::IO_DEVICE_TYPE ioDeviceType) {
  MaterialRegular materialRegular;
  QList<QTreeWidgetItem *> ioDeviceListViewStructList;
  QString queryString = "SELECT io.id AS io_id, io.description AS io_desc "
                        "FROM io_device io "
                        "INNER JOIN io_device_type io_dev_type ON io.type_id = io_dev_type.id "
                        "WHERE io.type_id =:type_id ";

  try {

    QSqlDatabase db;
    bsfDbConfig.setSqlDatabase(db);
    QSqlQuery query(db);

    db.open();
    query.prepare(queryString);
    query.bindValue(":type_id", (int) ioDeviceType);

    query.exec();

    while (query.next()) {
      auto *treeWidgetItem = new QTreeWidgetItem;
      treeWidgetItem->setData(0, Qt::UserRole, query.value("io_id").toInt());
      treeWidgetItem->setData(1, Qt::UserRole, ioDeviceType);

      if (ioDeviceType == IODeviceType::DETECTIONSENSOR) {
        treeWidgetItem->setData(2, Qt::UserRole, IODevice::IO_DEVICE_HIGH_LOW::HIGH);
        treeWidgetItem->setIcon(2, materialRegular.visibilityOffIcon());
      } else if (ioDeviceType == IODeviceType::RELAY) {
        treeWidgetItem->setData(2, Qt::UserRole, IODevice::IO_DEVICE_HIGH_LOW::HIGH);
        treeWidgetItem->setIcon(2, materialRegular.boltIcon(Qt::red));
      }

      treeWidgetItem->setData(3, Qt::DisplayRole, query.value("io_desc").toString());

      ioDeviceListViewStructList.append(treeWidgetItem);
    }

    db.close();

  }
  catch (std::exception &e) {
    printf("\n%s", e.what());
  }

  return ioDeviceListViewStructList;
}

QVector<IODevice *>
IODeviceRepository::getArduinoIODeviceList(int arduinoId,
                                           int ioDeviceTypeId,
                                           IODeviceType::IO_DEVICE_TYPE ioDeviceType) {
  QVector<IODevice *> ioDeviceList;
  QString queryString =
      "SELECT io.id AS io_id, io.arduino_id, io.type_id, io.action_id, io.description AS io_desc, io_dev_type.type AS io_type, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, act.code, act.url, act.description AS act_desc "
      "FROM io_device io "
      "INNER JOIN io_device_type io_dev_type ON io.type_id = io_dev_type.id "
      "INNER JOIN arduino ard ON ard.id = io.arduino_id "
      "INNER JOIN action act ON act.id = io.action_id "
      "WHERE io.type_id =:type_id AND io.arduino_id =:arduino_id "
      "ORDER BY io.action_id";

  try {
    if (ioDeviceTypeId > 0 && arduinoId > 0) {

      QSqlDatabase db;
      bsfDbConfig.setSqlDatabase(db);
      QSqlQuery query(db);

      db.open();
      query.prepare(queryString);
      query.bindValue(":type_id", ioDeviceTypeId);
      query.bindValue(":arduino_id", arduinoId);

      query.exec();

      switch (ioDeviceType) {
        case IODeviceType::RELAY :createRelayList(query, ioDeviceList);
          break;
        case IODeviceType::WEIGHTSENSOR:createWeightSensorList(query, ioDeviceList);
          break;
        case IODeviceType::DETECTIONSENSOR:createDetectionSensorList(query, ioDeviceList);
          break;
        case IODeviceType::UNKOWN:printf("\nunknown device type in method getArduinoIODeviceList");
          break;
        case IODeviceType::ARDUINO:break;
      }

      db.close();
    }
  }
  catch (std::exception &e) {
    printf("\n%s", e.what());
  }

  return ioDeviceList;
}

void IODeviceRepository::createRelayList(QSqlQuery &query, QVector<IODevice *> &list) {
  while (query.next()) {
    auto *relay = new Relay(query.value("io_id").toInt(), IODevice::HIGH);
    relay->setDescription(query.value("io_desc").toString());
    // Arduino properties
    auto arduino = new Arduino(query.value("arduino_id").toInt());
    arduino->setDesc(query.value("ard_desc").toString());
    arduino->setIpAddress(query.value("ipaddress").toString());
    arduino->setName(query.value("name").toString());
    arduino->setPort(query.value("port").toInt());
    relay->setArduino(arduino);
    // IODeviceType properties
    IODeviceType ioDeviceType = IODeviceType(query.value("type_id").toInt());
    ioDeviceType.setType(query.value("io_type").toString());
    IODeviceType::identifyIODeviceTypeEnum(ioDeviceType);
    relay->setIoDeviceType(ioDeviceType);
    // Action properties
    Action action = Action(query.value("action_id").toInt());
    action.setCode(query.value("code").toString());
    action.setUrl(query.value("url").toString());
    action.setDescription(query.value("act_desc").toString());
    relay->setAction(action);
    // ADD TO LIST
    list.append(relay);
  }
}

void IODeviceRepository::createDetectionSensorList(QSqlQuery &query, QVector<IODevice *> &list) {
  while (query.next()) {
    auto detectionSensor = new DetectionSensor(query.value("io_id").toInt(), IODevice::HIGH);
    detectionSensor->setDescription(query.value("io_desc").toString());
    // Arduino properties
    auto arduino = new Arduino(query.value("arduino_id").toInt());
    arduino->setDesc(query.value("ard_desc").toString());
    arduino->setIpAddress(query.value("ipaddress").toString());
    arduino->setName(query.value("name").toString());
    arduino->setPort(query.value("port").toInt());
    detectionSensor->setArduino(arduino);
    // IODeviceType properties
    IODeviceType ioDeviceType = IODeviceType(query.value("type_id").toInt());
    ioDeviceType.setType(query.value("io_type").toString());
    IODeviceType::identifyIODeviceTypeEnum(ioDeviceType);
    detectionSensor->setIoDeviceType(ioDeviceType);
    // Action properties
    Action action = Action(query.value("action_id").toInt());
    action.setCode(query.value("code").toString());
    action.setUrl(query.value("url").toString());
    action.setDescription(query.value("act_desc").toString());
    detectionSensor->setAction(action);
    // ADD TO LIST
    list.append(detectionSensor);
  }
}

void IODeviceRepository::createWeightSensorList(QSqlQuery &query, QVector<IODevice *> &list) {
  while (query.next()) {
    auto weightSensorDevice = new WeightSensor(query.value("io_id").toInt(), IODevice::HIGH);
    weightSensorDevice->setDescription(query.value("io_desc").toString());
    // Arduino properties
    auto arduino = new Arduino(query.value("arduino_id").toInt());
    arduino->setDesc(query.value("ard_desc").toString());
    arduino->setIpAddress(query.value("ipaddress").toString());
    arduino->setName(query.value("name").toString());
    arduino->setPort(query.value("port").toInt());
    weightSensorDevice->setArduino(arduino);
    // IODeviceType properties
    IODeviceType ioDeviceType = IODeviceType(query.value("type_id").toInt());
    ioDeviceType.setType(query.value("io_type").toString());
    IODeviceType::identifyIODeviceTypeEnum(ioDeviceType);
    weightSensorDevice->setIoDeviceType(ioDeviceType);
    // Action properties
    Action action = Action(query.value("action_id").toInt());
    action.setCode(query.value("code").toString());
    action.setUrl(query.value("url").toString());
    action.setDescription(query.value("act_desc").toString());
    weightSensorDevice->setAction(action);
    // ADD TO LIST
    list.append(weightSensorDevice);
  }
}

