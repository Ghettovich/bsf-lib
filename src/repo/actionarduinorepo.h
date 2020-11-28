#ifndef BSF_ACTIONARDUINOREPO_H
#define BSF_ACTIONARDUINOREPO_H

#include <bsfdatabaseconfig.h>
#include <action.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class ActionArduinoRepository {

public:
    ActionArduinoRepository(const QString & = "");
    QVector<Action> getArduinoAction(int arduino_id);

private:
    BsfDbconfig bsfDbConfig;
};
#endif //BSF_ACTIONARDUINOREPO_H
