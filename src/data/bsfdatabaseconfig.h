#ifndef BSF_DATABASECONFIG_H
#define BSF_DATABASECONFIG_H

#include <QtCore/QString>
#include <QtSql/QSqlDatabase>

class BsfDbconfig {

 public:
  BsfDbconfig();
  const QString database = "QSQLITE";
  const QString defaultConnection = "qt_sql_default_connection";
  void initDatabaseConnection();

  void setDatabaseName(const QString &);
  void setSqlDatabase(QSqlDatabase &);

  QSqlDatabase defaultSqlDatabase();

 private:
  QString databaseName = "";
  QSqlDatabase defaultDatabase;
  QString defaultDatabaseName = "data/bsf.db";
};
#endif //BSF_DATABASECONFIG_H
