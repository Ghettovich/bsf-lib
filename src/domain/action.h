#ifndef BSF_ACTION_H
#define BSF_ACTION_H

#include <QtCore/QString>

class Action
{

public:
    Action(int id = 0);
    int getId();
    QString getCode() const;
    void setCode(const QString &);
    QString getUrl() const;
    void setUrl(const QString &);
    QString getDescription() const;
    void setDescription(const QString &);

private:
    int id;
    QString code;
    QString url;
    QString description;
};
#endif //BSF_ACTION_H
