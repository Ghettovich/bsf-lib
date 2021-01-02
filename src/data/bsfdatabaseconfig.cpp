#include "bsfdatabaseconfig.h"
#include <QDir>
#include <QDebug>

BsfDbconfig::BsfDbconfig() {
}

void BsfDbconfig::initDatabaseConnection() {
  QDir dir(".");
  if (databaseName.isEmpty()) {

    databaseName = dir.absoluteFilePath("bsf.db");

  }

  printf("\n\n *** \nAbsolute path = %s", qUtf8Printable(dir.absolutePath()));
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
