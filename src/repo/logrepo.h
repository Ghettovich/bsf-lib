#ifndef BSF_LOGREPO_H
#define BSF_LOGREPO_H

#include <bsfdatabaseconfig.h>
#include <bafalog.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class LogRepository
{

public:
    LogRepository(const QString &connection = "");
    QVector<BafaLog> createBsfLogList();
    void addLog(const QString &logMsg, BafaLog::LOG_SEVERITY logSeverity);

private:
    BsfDbconfig bsfDbConfig;
    void insert(BafaLog &);

};
#endif //BSF_LOGREPO_H
