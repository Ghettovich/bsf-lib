#ifndef BSF_DATABASECONFIG_H
#define BSF_DATABASECONFIG_H

#include <QtCore/QString>
#include <QtSql/QSqlDatabase>

class BsfDbconfig {

public:
    BsfDbconfig();
    const QString defaultDatabaseName = "/home/mrfunkyman/Documents/databases/bsf/debug/bsf.db";
    const QString database = "QSQLITE";
    const QString defaultConnection = "qt_sql_default_connection";
    void initDatabaseConnection();

    void setDatabaseName(const QString &);
    void setSqlDatabase(QSqlDatabase&);

private:
    QString databaseName = "";

};
#endif //BSF_DATABASECONFIG_H
