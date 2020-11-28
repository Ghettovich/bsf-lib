#include "statecoderepo.h"
#include <QtSql/QSqlQuery>
#include <QtSql/qsqlquerymodel.h>

StateCodeRepository::StateCodeRepository(const QString& connection) {
    if(!connection.isEmpty()) {
        bsfDbConfig.setDatabaseName(connection);
    }
}

StateCode StateCodeRepository::getStateCode(int stateCodeId) {
    QString queryString = "SELECT id, message, status_message FROM state_code WHERE id =:id ";

    try {
        QSqlDatabase db;

        bsfDbConfig.setSqlDatabase(db);

        //setDefaultDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", stateCodeId);
        query.exec();

        if (query.first()) {
            StateCode stateCode = StateCode(query.value("id").toInt());
            stateCode.setMessage(query.value("message").toString());
            stateCode.setStatusMessage(query.value("status_message").toString());

            return stateCode;
        }
    } catch (std::exception &e) {
        printf("%s", e.what());
    }

    return StateCode(-1);
}
