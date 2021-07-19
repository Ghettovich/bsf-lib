#include "reciperepo.h"

#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>

RecipeRepository::RecipeRepository(std::shared_ptr<service::DatabaseService> &_databaseService, QObject *parent) :
    QObject(parent), databaseService(_databaseService) {

}

QVector<Recipe> RecipeRepository::getRecipes() {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString = "SELECT id, description FROM recipe";

  if (!query.exec(queryString)) {
    qDebug("DB table \"recipe\" findAll, Either select query error or table does not exists!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }

  QVector<Recipe> recipeList;

  while (query.next()) {
    Recipe recipe = Recipe(query.value("id").toInt());
    recipe.setDescription(query.value("description").toString());
    recipeList.append(recipe);
  }

  return recipeList;
}

Recipe RecipeRepository::getRecipeWithComponents(int id) {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString =
      "SELECT r.id AS r_id, r.description, c.id AS component_id, c.component, rp.target_weight, rp.margin_value FROM recipe r "
      "INNER JOIN recipe_components rp ON  r.id = rp.recipe_id "
      "INNER JOIN component c ON rp.component_id = c.id "
      "WHERE r.id =:id ";

  query.prepare(queryString);
  query.bindValue(":id", id);

  if (!query.exec()) {
    qDebug("DB table \"recipe 2\" findAll, Either select query error or table does not exists!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }

  Recipe recipe;

  if (query.first()) {
    recipe = Recipe(query.value("r_id").toInt());
    recipe.setDescription(query.value("description").toString());

    Component comp;
    addComponent(recipe.getId(), comp, recipe.componentList, query);

    while (query.next()) {
      addComponent(recipe.getId(), comp, recipe.componentList, query);
    }

    return recipe;
  }

  return Recipe(0);
}

Recipe RecipeRepository::getRecipe(int id) {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString = "SELECT id, description FROM recipe WHERE id =:id ";

  query.prepare(queryString);
  query.bindValue(":id", id);

  if (!query.exec()) {
    qDebug("DB table \"io_device\" findAll, Either select query error or table does not exists!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }

  Recipe recipe;

  if (query.first()) {
    recipe = Recipe(query.value("id").toInt());
    recipe.setDescription(query.value("description").toString());
    return recipe;
  }

  return Recipe(0);
}

void RecipeRepository::addComponent(int recipeId, Component &comp, QVector<Component> &compList, QSqlQuery &query) {
  comp = Component(query.value("component_id").toInt());
  comp.setRecipeId(recipeId);
  comp.setComponent(query.value("component").toString());
  comp.setTargetWeight(query.value("target_weight").toInt());
  comp.setMarginValue(query.value("margin_value").toInt());
  comp.setRecipeComponent(comp.identifyComponent(comp.getComponentId()));

  compList.append(comp);
}
