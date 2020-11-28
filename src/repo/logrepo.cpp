#include "logrepo.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QDateTime>
#include <QMetaEnum>

LogRepository::LogRepository(const QString &connection)
{
    if (!connection.isEmpty()) {
        bsfDbConfig.setDatabaseName(connection);
    }
}

void LogRepository::addLog(const QString &logMsg, BafaLog::LOG_SEVERITY logSeverity)
{
    BafaLog newLog = BafaLog();
    newLog.setLog(logMsg);
    newLog.setLogSeverity(logSeverity);
    insert(newLog);
}

QVector<BafaLog> LogRepository::createBsfLogList()
{
    QVector<BafaLog> logList = QVector<BafaLog>();
    QString queryString = "SELECT id, logtype, log, logdatetime FROM log";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery q(db);

        db.open();
        q.exec(queryString);

        while (q.next()) {
            BafaLog log = BafaLog(q.value("id").toInt());
            log.setLogType(q.value("logtype").toInt());
            log.setLog(q.value("log").toString());
            log.setLogDateTime(q.value("logdatetime").toInt());
            log.setLogSeverity(BafaLog::LOG_SEVERITY(log.getLogType()));
            logList.append(log);
        }

        db.close();

    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return logList;
}

void LogRepository::insert(BafaLog &log)
{
    log.determineLogSeverity();
    BsfDbconfig bsfDbconfig = BsfDbconfig();

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);
        db.open();

        query.prepare("INSERT INTO log (logtype, log, logdatetime) VALUES (:logtype, :log, :logdatetime)");
        query.bindValue(":logtype", log.getLogType());
        query.bindValue(":log", log.getLog());
        query.bindValue(":logdatetime", QDateTime::currentSecsSinceEpoch());
        query.exec();

        db.close();
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }
}
