#ifndef BSF_BAFALOG_H
#define BSF_BAFALOG_H

#include <QObject>
#include <QtCore/QString>

class BafaLog
{

Q_GADGET

public:
    enum LOG_SEVERITY
    {
        UNKNOWN, ERROR, WARNING, INFO
    };
    Q_ENUM(LOG_SEVERITY);

    explicit BafaLog(int id = 0);

    int getId() const;
    int getLogType() const;
    void setLogType(int severity);
    qint64 getLogDateTime() const;
    void setLogDateTime(qint64);
    QString getLog() const;
    void setLog(const QString &logMessage);
    LOG_SEVERITY getLogSeverity() const;
    void setLogSeverity(LOG_SEVERITY);
    void determineLogSeverity();

private:
    int id;
    int logType;
    qint64 logDateTime;
    QString log;
    LOG_SEVERITY logSeverity;
};

#endif //BSF_BAFALOG_H
