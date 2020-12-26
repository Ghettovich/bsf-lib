#include "bsfdatabaseconfig.h"

BsfDbconfig::BsfDbconfig() {
}

void BsfDbconfig::initDatabaseConnection() {
  if (databaseName.isEmpty()) {
    databaseName = defaultDatabaseName;
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
