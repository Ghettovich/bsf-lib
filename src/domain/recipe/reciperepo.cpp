#include "reciperepo.h"

#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>

RecipeRepository::RecipeRepository(std::shared_ptr<service::DatabaseService> &_databaseService, QObject *parent) :
    QObject(parent), databaseService(_databaseService) {
}

QVector<Recipe> RecipeRepository::getRecipes() {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString = "SELECT id, title, description, error_margin FROM recipe";

  if (!query.exec(queryString)) {
    qDebug("DB table \"recipe\" findAll, Either select query error or table does not exists!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }

  QVector<Recipe> recipeList;

  while (query.next()) {
    Recipe recipe = Recipe(query.value("id").toInt());
    recipe.setTitle(query.value("title").toString());
    recipe.setDescription(query.value("description").toString());
    recipe.setErrorMargin(query.value("error_margin").toDouble());

    recipeList.append(recipe);
  }

  return recipeList;
}

std::unique_ptr<Recipe> RecipeRepository::getRecipe(int recipeId) {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString =
      "SELECT r.id, r.title, r.description "
      "FROM recipe r "
      "WHERE r.id =:id ";

  query.prepare(queryString);
  query.bindValue(":id", recipeId);

  if (!query.exec()) {
    qDebug("DB table \"recipe\" getRecipe, Either select query error or table does not exists!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }

  if (query.first()) {
    auto recipe = std::make_unique<Recipe>(query.value("id").toInt());

    recipe->setTitle(query.value("title").toString());
    recipe->setDescription(query.value("description").toString());

    auto materials = getMaterials(recipe->getId());
    recipe->setMaterials(materials);

    auto components = getComponents(recipe->getId());
    recipe->setComponents(components);

    return recipe;
  }

  return {};
}
QList<Material> RecipeRepository::getMaterials(int recipeId) {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString =
      "SELECT rm.id, m.name, m.description, rm.weight "
      "FROM recipe_material rm "
      "INNER JOIN material m ON m.id = rm.material_id "
      "WHERE rm.recipe_id =:id ";

  query.prepare(queryString);
  query.bindValue(":id", recipeId);

  if (!query.exec()) {
    qDebug("DB table \"recipe\" getMaterials, Either select query error or table does not exists!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }

  QList<Material> materials;

  while(query.next()) {
    Material material(query.value("id").toInt(),
                      query.value("weight").toDouble(),
                      query.value("name").toString(),
                      query.value("description").toString());

    materials.append(material);
  }

  return materials;
}
QList<Component> RecipeRepository::getComponents(int recipeId) {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString =
      "SELECT c.id AS comp_id, cr.id AS comp_ratio_id, cr.recipe_id AS recipe_id, c.description, c.name, cr.ratio, cr.weight "
      "FROM component c "
      "INNER JOIN component_ratio cr ON c.id = cr.component_id "
      "INNER JOIN recipe r ON r.id = cr.recipe_id "
      "WHERE cr.recipe_id =:id ";

  query.prepare(queryString);
  query.bindValue(":id", recipeId);

  if (!query.exec()) {
    qDebug("DB table \"recipe\" getComponents, Either select query error or table does not exists!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }

  QList<Component> components;

  while(query.next()) {
    Component comp(query.value("comp_ratio_id").toInt(),
                   query.value("comp_id").toInt(),
                   query.value("recipe_id").toInt(),
                   query.value("name").toString(),
                   query.value("description").toString(),
                   query.value("weight").toDouble(),
                   query.value("ratio").toDouble());

    components.append(comp);
  }

  return components;
}
void RecipeRepository::saveRecipe(const Recipe &recipe) {

}
void RecipeRepository::updateRecipeMaterial(int id, double weight) {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString = "UPDATE recipe_material SET weight=:weight WHERE id=:id;";

  query.prepare(queryString);
  query.bindValue(":weight", weight);
  query.bindValue(":id", id);

  if (!query.exec()) {
    qDebug("DB table \"recipe\" updateRecipeMaterial, updating recipe material failed!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }
}
void RecipeRepository::updateRecipeComponent(int id, double weight, double ratio) {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString = "UPDATE component_ratio SET weight=:weight, ratio=:ratio WHERE id=:id ";

  query.prepare(queryString);
  query.bindValue(":weight", weight);
  query.bindValue(":ratio", ratio);
  query.bindValue(":id", id);

  if (!query.exec()) {
    qDebug("DB table \"recipe\" updateRecipeComponent, updating recipe components failed!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }
}
void RecipeRepository::updateRecipe(int id, const QString &title, const QString &description, double errorMargin) {
  QSqlDatabase db = databaseService->openDatabase();
  QSqlQuery query(db);

  QString queryString = "UPDATE recipe SET title=:title, description=:description, error_margin=:error_margin "
                        "WHERE id=:id ";

  query.prepare(queryString);
  query.bindValue(":title", title);
  query.bindValue(":description", description);
  query.bindValue(":error_margin", errorMargin);
  query.bindValue(":id", id);

  if (!query.exec()) {
    qDebug("DB table \"recipe\" updateRecipe, updating recipe failed!");
    qDebug() << QString(query.lastError().text());
    throw std::logic_error("Unknown Exception");
  }
}
