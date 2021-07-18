#include "DatabaseService.h"
#include <QSettings>

using namespace service;

DatabaseService::DatabaseService(QObject *parent) : QObject(parent) {
  // Create a database connection to reconnect whenever it is required
  auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
  settings->beginGroup("database");

  QString dbPath = settings->value("path").toString();

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(dbPath);
  if (!db.open()) {
    qFatal("Failed to connect database: %s", qUtf8Printable(dbPath));
  }
}
DatabaseService::~DatabaseService() {
      foreach (QSqlDatabase connection, connections) {
      connection.close();
    }
}
void DatabaseService::runScripts(const QVector<QVector<QString>> &scripts) {
  QSqlQuery query(QSqlDatabase::database());

  foreach(QVector<QString> script, scripts) {

      for (auto &i : script) {
        if (!query.exec(i)) {
          qDebug() << QString(query.lastError().text());
          qFatal("Failed to execute script");
        }
      }
  }
}
QSqlDatabase DatabaseService::openDatabase() {
  auto id = int64_t(QThread::currentThreadId());
  if (connections.contains(id)) {
    return connections[id];
  } else {
    auto settings = new QSettings(":settings.ini", QSettings::IniFormat, this);
    settings->beginGroup("database");

    QString dbPath = settings->value("path").toString();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString::number(id));
    connections.insert(id, db);

    db.setDatabaseName(dbPath);
    db.open();
    return db;
  }
}


