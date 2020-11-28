#ifndef BSF_STATECODE_H
#define BSF_STATECODE_H

#include <QObject>
#include <QtCore/QString>

class StateCode
{

public:

    explicit StateCode(int id = 0);
    int getId() const;
    const QString &getStatusMessage() const;
    void setStatusMessage(const QString &_message);
    const QString &getMessage() const;
    void setMessage(const QString &);

private:
    int id;
    QString message;
    QString statusMessage;

};

#endif //BSF_STATECODE_H
