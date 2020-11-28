#include "arduinorepo.h"
#include <iodevicetype.h>
#include <detectionsensor.h>
#include <relay.h>
#include <weightcensor.h>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>

ArduinoRepository::ArduinoRepository(const QString &connection)
{
    if (!connection.isEmpty()) {
        bsfDbConfig.setDatabaseName(connection);
    }
};

QVector<Arduino> ArduinoRepository::getAllActiveArduino()
{
    QString queryString = "SELECT id, name, ipaddress, port, description FROM arduino";
    QVector<Arduino> arduinoList;

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);

        QSqlQuery query(db);

        db.open();
        query.exec(queryString);

        while (query.next()) {
            Arduino arduino = Arduino(query.value("id").toInt());
            arduino.setDesc(query.value("description").toString());
            arduino.setIpAddress(query.value("ipaddress").toString());
            arduino.setName(query.value("name").toString());
            arduino.setPort(query.value("port").toInt());
            arduinoList.append(arduino);
        }

        db.close();
    }
    catch (std::exception &e) {
        printf("%s", e.what());
    }
    return arduinoList;
}

QList<QTreeWidgetItem *> ArduinoRepository::getArduinoTreeWidgets()
{
    QString queryString = "SELECT id, name FROM arduino";
    QList<QTreeWidgetItem *> arduinoTreeWidgetItemList;

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);

        QSqlQuery query(db);

        db.open();
        query.exec(queryString);

        while (query.next()) {
            auto treeWidgetItem = new QTreeWidgetItem;
            treeWidgetItem->setData(0, Qt::UserRole, query.value("id").toInt());
            treeWidgetItem->setData(1, Qt::DisplayRole, IODevice::IO_DEVICE_HIGH_LOW::LOW);
            treeWidgetItem->setData(2, Qt::DisplayRole, query.value("name").toString());

            arduinoTreeWidgetItemList.append(treeWidgetItem);
        }

        db.close();

    }
    catch (std::exception &e) {
        printf("%s", e.what());
    }

    return arduinoTreeWidgetItemList;
}

Arduino ArduinoRepository::getArduino(int id)
{
    Arduino arduino;
    QString queryString = "SELECT id, name, ipaddress, port, description FROM arduino WHERE id =:id";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", id);
        query.exec();

        if (query.first()) {
            arduino = Arduino(query.value("id").toInt());
            arduino.setDesc(query.value("description").toString());
            arduino.setIpAddress(query.value("ipaddress").toString());
            arduino.setName(query.value("name").toString());
            arduino.setPort(query.value("port").toInt());
            return arduino;
        }

        db.close();
    }
    catch (std::exception &e) {
        printf("%s", e.what());
    }

    return Arduino(0);
}

void ArduinoRepository::updateArduino(const Arduino &arduinoDevice)
{
    QString
        queryString = "UPDATE arduino SET description=:desc, ipaddress=:ipaddress, name=:name, port=:port WHERE id=:id";

    try {
        if (arduinoDevice.getId() > 0) {
            QSqlDatabase db;
            bsfDbConfig.setSqlDatabase(db);
            QSqlQuery query(db);

            db.open();
            query.prepare(queryString);
            query.bindValue(":desc", arduinoDevice.getDesc());
            query.bindValue(":ipaddress", arduinoDevice.getIpAddress());
            query.bindValue(":name", arduinoDevice.getName());
            query.bindValue(":port", arduinoDevice.getPort());
            query.bindValue(":id", arduinoDevice.getId());

            query.exec();
            db.close();
        }

    }
    catch (std::exception &e) {
        printf("%s", e.what());
    }
}

Arduino ArduinoRepository::getActiveArduinoWithIODevices(int arduinoId)
{
    QString queryString =
        "SELECT io.arduino_id, ard.description AS ard_desc, ard.ipaddress, ard.name, ard.port, io.id AS io_id, io.type_id, io.action_id, io.description AS io_desc, io_dev_type.type AS io_type, act.code, act.url, act.description AS act_desc "
        "FROM io_device io "
        "INNER JOIN io_device_type io_dev_type ON io.type_id = io_dev_type.id "
        "INNER JOIN arduino ard ON ard.id = io.arduino_id "
        "INNER JOIN action act ON act.id = io.action_id "
        "WHERE ard.id =:id "
        "ORDER BY io.arduino_id ";
    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", arduinoId);
        query.exec();

        if (query.first()) {
            Arduino arduino(query.value("arduino_id").toInt());
            arduino.setDesc(query.value("ard_desc").toString());
            arduino.setIpAddress(query.value("ipaddress").toString());
            arduino.setName(query.value("name").toString());
            arduino.setPort(query.value("port").toInt());

            while (query.next()) {
                IODevice *ioDevice = createIODeviceFromResult(query);
                arduino.addIODevice(ioDevice);
            }

            return arduino;
        }

    }
    catch (std::exception &e) {
        printf("%s", e.what());
    }

    return Arduino(0);
}

IODevice *ArduinoRepository::createIODeviceFromResult(const QSqlQuery &query)
{
    IODevice *ioDevice = nullptr;
    // IODeviceType properties
    IODeviceType ioDeviceType = IODeviceType(query.value("type_id").toInt());
    ioDeviceType.setType(query.value("io_type").toString());
    IODeviceType::identifyIODeviceTypeEnum(ioDeviceType);

    if (ioDeviceType.getIODeviceType() == IODeviceType::DETECTIONSENSOR) {
        ioDevice = new DetectionSensor(query.value("io_id").toInt(), IODevice::HIGH);
    }
    else if (ioDeviceType.getIODeviceType() == IODeviceType::RELAY) {
        ioDevice = new Relay(query.value("io_id").toInt(), IODevice::HIGH);
    }
    else if (ioDeviceType.getIODeviceType() == IODeviceType::WEIGHTSENSOR) {
        ioDevice = new WeightSensor(query.value("io_id").toInt(), IODevice::HIGH);
    }
    else {
        printf("\nUnkown device");
    }
    // Action properties
    Action action = Action(query.value("action_id").toInt());
    action.setCode(query.value("code").toString());
    action.setUrl(query.value("url").toString());
    action.setDescription(query.value("act_desc").toString());
    // call setters after null pointer check
    if (ioDevice != nullptr) {
        ioDevice->setIoDeviceType(ioDeviceType);
        ioDevice->setAction(action);
        return ioDevice;
    }
    else {
        return nullptr;
    }
}
