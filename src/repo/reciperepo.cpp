#include "reciperepo.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>


RecipeRepository::RecipeRepository(const QString &connection)
{
    if (!connection.isEmpty()) {
        bsfDbConfig.setDatabaseName(connection);
    }
}

QVector<Recipe> RecipeRepository::getRecipes()
{
    QVector<Recipe> recipeList;
    QString queryString = "SELECT id, description FROM recipe";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);
        db.open();

        if (query.exec(queryString)) {
            while (query.next()) {
                Recipe recipe = Recipe(query.value("id").toInt());
                recipe.setDescription(query.value("description").toString());
                recipeList.append(recipe);
            }
        }

    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return recipeList;
}

Recipe RecipeRepository::getRecipeWithComponents(int id)
{
    Recipe recipe;
    QString queryString =
        "SELECT r.id AS r_id, r.description, c.id AS component_id, c.component, rp.target_weight, rp.margin_value FROM recipe r "
        "INNER JOIN recipe_components rp ON  r.id = rp.recipe_id "
        "INNER JOIN component c ON rp.component_id = c.id "
        "WHERE r.id =:id ";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", id);
        query.exec();

        if (query.first()) {
            recipe = Recipe(query.value("r_id").toInt());
            recipe.setDescription(query.value("description").toString());

            Component comp;
            addComponent(recipe.getId(), comp, recipe.componentList, query);

            while (query.next()) {
                addComponent(recipe.getId(),comp, recipe.componentList, query);
            }

            return recipe;
        }
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return Recipe(0);
}

Recipe RecipeRepository::getRecipe(int id)
{
    Recipe recipe;
    QString queryString = "SELECT id, description FROM recipe WHERE id =:id ";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);

        db.open();
        query.prepare(queryString);
        query.bindValue(":id", id);
        query.exec();

        if (query.first()) {
            recipe = Recipe(query.value("id").toInt());
            recipe.setDescription(query.value("description").toString());
            return recipe;
        }
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return Recipe(0);
}

void RecipeRepository::addComponent(int recipeId, Component &comp, QVector<Component> &compList, QSqlQuery &query)
{
    comp = Component(query.value("component_id").toInt());
    comp.setRecipeId(recipeId);
    comp.setComponent(query.value("component").toString());
    comp.setTargetWeight(query.value("target_weight").toInt());
    comp.setMarginValue(query.value("margin_value").toInt());
    comp.setRecipeComponent(comp.identifyComponent(comp.getComponentId()));

    compList.append(comp);
}
QList<QTreeWidgetItem *> RecipeRepository::getRecipesTreeWidgetList()
{
    QList<QTreeWidgetItem *> recipeTreeWidgets;
    QString queryString = "SELECT id, description FROM recipe";

    try {
        QSqlDatabase db;
        bsfDbConfig.setSqlDatabase(db);
        QSqlQuery query(db);
        db.open();

        if (query.exec(queryString)) {
            while (query.next()) {
                auto treeWidgetItem = new QTreeWidgetItem;
                treeWidgetItem->setData(0, Qt::UserRole, query.value("id").toInt());
                treeWidgetItem->setData(0, Qt::DisplayRole, query.value("description").toString());
                recipeTreeWidgets.append(treeWidgetItem);
            }
        }
    }
    catch (std::exception &e) {
        qDebug("%s", e.what());
    }

    return recipeTreeWidgets;
}


