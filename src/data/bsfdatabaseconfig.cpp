#include "bsfdatabaseconfig.h"
#include <QDir>
#include <QDebug>

BsfDbconfig::BsfDbconfig() {
  if (!QSqlDatabase::contains(defaultConnection)) {
    defaultDatabase = QSqlDatabase::addDatabase(database, defaultConnection);
  }
}

void BsfDbconfig::initDatabaseConnection() {
  if (databaseName.isEmpty()) {
    QDir dir(".");
    databaseName = dir.absoluteFilePath("bsf.db");
  }
}

void BsfDbconfig::setDatabaseName(const QString &_databaseName) {
  databaseName = _databaseName;
}

void BsfDbconfig::setSqlDatabase(QSqlDatabase &db) {
  initDatabaseConnection();

  if (!QSqlDatabase::contains(defaultConnection)) {
    db = QSqlDatabase::addDatabase(database, defaultConnection);
  } else {
    db = QSqlDatabase::database(defaultConnection);
  }
  db.setDatabaseName(databaseName);
}

QSqlDatabase BsfDbconfig::defaultSqlDatabase() {
  defaultDatabase.setDatabaseName(defaultDatabaseName);
  return QSqlDatabase();
}
