#ifndef BSF_RECIPEREPO_H
#define BSF_RECIPEREPO_H

#include "recipe.h"

#include <memory>
#include <QObject>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

#include <database/DatabaseService.h>

class RecipeRepository : public QObject {

 public:
  explicit RecipeRepository(std::shared_ptr<service::DatabaseService> &databaseService, QObject *parent = nullptr);
  Recipe getRecipe(int);
  Recipe getRecipeWithComponents(int);
  QVector<Recipe> getRecipes();

 private:
  std::shared_ptr<service::DatabaseService> databaseService;
  void addComponent(int recipeId, Component &, QVector<Component> &, QSqlQuery &);

};
#endif //BSF_RECIPEREPO_H
