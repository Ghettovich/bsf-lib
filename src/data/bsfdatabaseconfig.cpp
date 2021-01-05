#include "bsfdatabaseconfig.h"
#include <QDir>
#include <QDebug>

BsfDbconfig::BsfDbconfig() {
  if (!QSqlDatabase::contains(defaultConnection)) {
    defaultDatabase = QSqlDatabase::addDatabase(database, defaultConnection);
  }
}

void BsfDbconfig::initDatabaseConnection() {
  QDir dir(".");
  printf("\n\n *** PATH = %s\n", qUtf8Printable(dir.absolutePath()));

  if (databaseName.isEmpty()) {

    databaseName = dir.absoluteFilePath("bsf.db");
  }

  printf("\n\n *** DB NAME = %s", qUtf8Printable(databaseName));
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
