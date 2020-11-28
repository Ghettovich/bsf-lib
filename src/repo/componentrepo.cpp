#include "componentrepo.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>

ComponentRepo::ComponentRepo(const QString &connection)
{
    if (!connection.isEmpty()) {
        bsfDbConfig.setDatabaseName(connection);
    }
}

QVector<Component> ComponentRepo::getComponentsFromRecipe(int recipeId)
{
    QVector<Component> componentList;
    QString queryString = "SELECT c.id AS comp_id, c.component, rp.target_weight "
                          "FROM component c INNER JOIN recipe_components rp ON c.id = rp.component_id"
                          "WHERE rp.recipe_id :=id ";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", recipeId);
        query.exec();

        if (query.exec(queryString)) {
            while (query.next()) {
                Component comp(query.value("id").toInt());
                comp.setComponent(query.value("component").toString());
                comp.setTargetWeight(query.value("target_weigt").toInt());

                componentList.append(comp);
            }
        }

    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return componentList;
}
